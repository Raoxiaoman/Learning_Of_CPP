#include <stdlib.h>  
#include <stdio.h>
#include <sys/types.h>  
#include <unistd.h>  
  
int main()  
{  
    int count = 1;
    int child;  
  
    /* 创建一个子进程 */  
    child = vfork();  
    if(child<0){
        perror("fork error\n");
    }
    if(child == 0)  
    {  
        printf("child pid\n");  
        printf("count is %d (%p)\n",++count,&count);
        printf("pid is %d\n",getpid());  
        exit(0);  
        //不应该用return结束使用vfork创建的子进程，应该使用exit或_exit
    }  
    else  
    {  
        printf("father pid\n");  
        printf("count is %d (%p)\n",count,&count);
        printf("pid is %d\n",getpid());  
        sleep(2);  
    }  
      
    return 0;  
}  
