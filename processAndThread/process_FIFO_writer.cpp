#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

int main()
{
    int ff;
    char buff[1024] ;
    time_t tp;

    if(mkfifo("fifo1",0666) < 0 && errno!=EEXIST){
        perror("Create FIFO error\n");
        exit(1);
    }
    if((ff = open("fifo1",O_WRONLY))<0){
        
        perror("Create FIFO error\n");
        exit(1);
    }

    for(int i = 0;i<10;i++){
        time(&tp);
        printf("Writer Process id is %d\t", getpid());
        sprintf(buff, "time is %s",ctime(&tp));
        printf("message is %s\n", buff);
        if(write(ff,buff,1024)< 0){
            perror("Write FIFO error \n");
            close(ff);
            exit(1);

        }
        sleep(1);
    }

    return 0;
}

