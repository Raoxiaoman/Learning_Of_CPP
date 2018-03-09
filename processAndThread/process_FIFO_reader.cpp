#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>


int  main()
{
    int ff;
    char buff[1024] ;

    if((ff = open("fifo1",O_RDONLY))<0){
        perror("Create FIFO error\n");
        exit(1);
    }


    while(read(ff,buff,1024) > 0){
        printf("Reader Process id is %d\t", getpid());
        printf("%s\n",buff);
    }
    close(ff);
    return 0;
}

