#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>

#include "term.h"

#define STI STDIN_FILENO
#define STO STDOUT_FILENO

struct input_buf
{
    int len;
    char buf[1024];
} in_buf;

/**********************************************************************/

ssize_t
writen_ni(int fd, const void *buff, size_t n)
{
    size_t nl;
    ssize_t nw;
    const char *p;

    p = buff;
    nl = n;
    while (nl > 0)
    {
        do
        {
            nw = write(fd, p, nl);
        } while (nw < 0 && errno == EINTR);
        if (nw <= 0)
            break;
        nl -= nw;
        p += nw;
    }

    return n - nl;
}

void fatal(const char *format, ...)
{
    char *s, buf[256];
    va_list args;
    int len;

    term_reset(STO);
    term_reset(STI);

    va_start(args, format);
    len = vsnprintf(buf, sizeof(buf), format, args);
    buf[sizeof(buf) - 1] = '\0';
    va_end(args);

    s = "\r\nFATAL: ";
    writen_ni(STO, s, strlen(s));
    writen_ni(STO, buf, len);
    s = "\r\n";
    writen_ni(STO, s, strlen(s));

    /* wait a bit for output to drain */
    sleep(1);

#ifdef UUCP_LOCK_DIR
    uucp_unlock();
#endif

    exit(EXIT_FAILURE);
}



/* implemented caracter mappings */
#define M_CRLF   (1 << 0) /* map CR  --> LF */
#define M_CRCRLF (1 << 1) /* map CR  --> CR + LF */
#define M_IGNCR  (1 << 2) /* map CR  --> <nothing> */
#define M_LFCR   (1 << 3) /* map LF  --> CR */
#define M_LFCRLF (1 << 4) /* map LF  --> CR + LF */
#define M_IGNLF  (1 << 5) /* map LF  --> <nothing> */
#define M_DELBS  (1 << 6) /* map DEL --> BS */
#define M_BSDEL  (1 << 7) /* map BS  --> DEL */
#define M_NFLAGS 8


int
do_map (char *b, int map, char c)
{
	int n;
    
	switch (c) {
	case '\x7f':
		/* DEL mapings */
		if ( map & M_DELBS ) {
			b[0] = '\x08'; n = 1;
		} else {
			b[0] = c; n = 1;
		}
		break;
	case '\x08':
		/* BS mapings */
		if ( map & M_BSDEL ) {
			b[0] = '\x7f'; n = 1;
		} else {
			b[0] = c; n = 1;
		}
		break;
	case '\x0d':
		/* CR mappings */
		if ( map & M_CRLF ) {
			b[0] = '\x0a'; n = 1;
		} else if ( map & M_CRCRLF ) {
			b[0] = '\x0d'; b[1] = '\x0a'; n = 2;
		} else if ( map & M_IGNCR ) {
			n = 0;
		} else {
			b[0] = c; n = 1;
		}
		break;
	case '\x0a':
		/* LF mappings */
		if ( map & M_LFCR ) {
			b[0] = '\x0d'; n = 1;
		} else if ( map & M_LFCRLF ) {
			b[0] = '\x0d'; b[1] = '\x0a'; n = 2;
		} else if ( map & M_IGNLF ) {
			n = 0;
		} else {
			b[0] = c; n = 1;
		}
		break;
	default:
		b[0] = c; n = 1;
  
		break;
	}

	return n;
}


/* default character mappings */
#define M_I_DFL 0
#define M_O_DFL 0
#define M_E_DFL (M_DELBS | M_CRCRLF)


int main(int argc, char *argv[])
{
    int write_fd, read_fd;
    int n;
    char *write_fifo, *read_fifo;
    char cr = '\x0d';
    char c;

    write_fifo = "/tmp/stiff";
    read_fifo = "/tmp/stoff";

    if (access(write_fifo, F_OK) == -1)
    {
        if ((mkfifo(write_fifo, 0777)) != 0)
        {
            fprintf(stderr, "Could not create fifo %s\n", write_fifo);
            exit(EXIT_FAILURE);
        }
    }
    if (access(read_fifo, F_OK) == -1)
    {
        if ((mkfifo(read_fifo, 0777)) != 0)
        {
            fprintf(stderr, "Could not create fifo %s\n", read_fifo);
            exit(EXIT_FAILURE);
        }
    }
    if ((write_fd = open(write_fifo, O_RDWR | O_NONBLOCK)) < 0)
        fatal("cannot open %s: %s\n", write_fifo, strerror(errno));
    if ((read_fd = open(read_fifo, O_RDWR | O_NONBLOCK)) < 0)
        fatal("cannot open %s: %s\n", read_fifo, strerror(errno));

    for (;;)
    {

        enum
        {
            TRANS_ONGOING,
            TRANS_OK
        } state;

        state = TRANS_ONGOING;
        in_buf.len = 0;

        fd_set rdset, wrset;

        FD_ZERO(&rdset);
        FD_ZERO(&wrset);
        FD_SET(STI, &rdset);
        FD_SET(read_fd, &rdset);
        FD_SET(write_fd, &wrset);

        if (select(write_fd + 10, &rdset, &wrset, NULL, NULL) < 0)
            fatal("select failed: %d : %s", errno, strerror(errno));

        if (FD_ISSET(STI, &rdset))
        {

            do
            {
                n = read(STI, &c, 1);
            } while (n < 0 && errno == EINTR);
            if (n == 0)
            {
                fatal("stdin closed");
            }
            else if (n < 0)
            {
                /* is this really necessary? better safe than sory! */
                if (errno != EAGAIN && errno != EWOULDBLOCK)
                    fatal("read from stdin failed: %s", strerror(errno));
            }else{
            
			    n = do_map((char *)in_buf.buf + in_buf.len,  M_E_DFL,c);
			    in_buf.len += n;
            }
            
        }

    skip_proc_STI:

        if (FD_ISSET(write_fd, &wrset))
        {
            if (in_buf.len > 0 )
            {
                // in_buf.buf[in_buf.len+1]='\x0d';
                // in_buf.len += 1;
         
                n = write(write_fd, in_buf.buf, in_buf.len);
                write(STO,in_buf.buf,in_buf.len);
                in_buf.len -= n;
            }
        }

        if (FD_ISSET(read_fd, &rdset))
        {
            if (read(read_fd, &c, 1) > 0)
            {
                printf("%c", c);
            }
        }
    }

    /* remove the FIFO */
    //unlink(myfifo);

    return 0;
}