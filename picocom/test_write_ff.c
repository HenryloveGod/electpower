#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    int fd;
    char * myfifo = argv[1];


    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    printf("write to fifo %s\n" , myfifo);

    /* write "Hi" to the FIFO */
    fd = open(myfifo, O_WRONLY  | O_NONBLOCK);
    write(fd, "Hi", sizeof("Hi"));
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);

    return 0;
}