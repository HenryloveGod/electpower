#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>



#define MAX_BUF 1024

int main(int argc, char *argv[])
{
    int fd;
    char * myfifo = argv[1];
    char buf[MAX_BUF];


    /* create the FIFO (named pipe) */
    //mkfifo(myfifo, 0666);
    printf("read from fifo %s\n" , myfifo);


    fd_set rdset, wrset;

    mkfifo(myfifo, S_IRWXU);

    fd = open(myfifo, O_RDONLY  | O_NONBLOCK);


    for(;;){


		FD_ZERO(&rdset);
		FD_ZERO(&wrset);
		FD_SET(fd, &rdset);
	
        if (select(fd + 1, &rdset, &wrset, NULL, NULL) < 0){
            perror("----------exit for select ERROR!\n");
        }

        if ( FD_ISSET(fd, &rdset) ){
            if(read(fd, buf, MAX_BUF) >0){
                printf("Received: %s\n", buf);
            }
        }
   
        
    }


    close(fd);

    return 0;
}