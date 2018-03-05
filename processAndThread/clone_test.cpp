#include <stdlib.h>  
#include <stdio.h>
#include <malloc.h>
#include <sched.h>
#include <sys/types.h>  
#include <unistd.h>  
  
#define STACK_SIZE 8192
int count;
int dosomething(void *stack){
    printf("child thread \n");  
    printf("count is %d (%p)\n",++count,&count);
    printf("pid is %d\n",getpid());  
    free(stack);
    exit(1);

}

int main()  
{  
    count  = 1;
    void *stack;
    stack= malloc(STACK_SIZE);

    if(!stack){
        perror("malloc error\n");
        exit(0);
    }
    /* 创建一个子进程 (线程)*/  
    printf("create a thread \n");  
    clone(&dosomething,(char *)stack+STACK_SIZE,CLONE_VM | CLONE_VFORK,0);
    printf("father pid\n");  
    printf("count is %d (%p)\n",count,&count);
    printf("pid is %d\n",getpid());  
    exit(1);

}  
