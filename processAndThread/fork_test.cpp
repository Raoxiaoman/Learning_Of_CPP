#include <stdlib.h>  
#include <stdio.h>
#include <sys/types.h>  
#include <unistd.h>  
  
int main()  
{  
    int count = 1;
    int child;  
  
    /* 创建一个子进程 */  
    child = fork();  

    if(child<0){
        perror("fork error\n");
    }
    else if(child == 0)  
    {  
        printf("child pid\n");  
        printf("count is %d (%p)\n",++count,&count);
        printf("pid is %d\n",getpid());  
        exit(0);
        
    }  
    else  
    {  
        printf("father pid\n");  
        printf("count is %d (%p)\n",count,&count);
        printf("pid is %d\n",getpid());  
        sleep(2);
        //exit(0);
    }  
      
    return EXIT_SUCCESS;  
}  
