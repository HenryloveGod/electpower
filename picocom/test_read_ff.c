#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
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
    for(;;){
    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY  | O_NONBLOCK);
   
        if(read(fd, buf, MAX_BUF) >0){
            printf("Received: %s\n", buf);
        }
    }


    close(fd);

    return 0;
}