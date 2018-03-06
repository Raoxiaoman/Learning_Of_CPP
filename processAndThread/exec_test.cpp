#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //以NULL结尾的字符串数组的指针，适合包含v的exec函数参数
    char args1[] = "ls";
    char args2[] = "-a";
    char *arg[] = {args1,args2,NULL};

    /**
     * 创建子进程并调用函数execl
     * execl 中希望接收以逗号分隔的参数列表，并以NULL指针为结束标志
     */
    if(vfork()==0){
        printf("----------execl-----------\n");
        if(execl("/bin/ls", "ls", "-a",NULL )==-1){
            perror("execl error");
            exit(1);

        }
    }

    /**
     * 创建子进程并调用 execlp
     * execlp中
     * l希望接收以逗号分隔的参数列表，列表以NULL指针作为结束标志
     * p是一个以NULL结尾的字符串数组指针，函数可以DOS的PATH变量查找子程序文件
     */
    if(vfork()==0){
        printf("----------execlp-----------\n");
        if(execlp("ls", "ls", "-a",NULL )==-1){
            perror("execv error");
            exit(1);

        }
    }

    /**
     * 创建子进程并调用函数execlp
     * execv中希望接收一个以NULL结尾的字符串数组的指针
     */
    if(vfork()==0){
        printf("----------execv-----------\n");
        if(execv("/bin/ls",arg) ==-1){
            perror("execv error");
            exit(1);

        }
    }

    /**
     *创建子里程并调用execvp
     *v 望接收到一个以NULL结尾的字符串数组的指针
     *p 是一个以NULL结尾的字符串数组指针，函数可以DOS的PATH变量查找子程序文件
     */
    if(vfork()==0){
        printf("----------execvp-----------\n");
        if(execvp("ls",arg) ==-1){
            perror("execvp error");
            exit(1);

        }
    }

    /**
     *创建子进程并调用execle
     *l 希望接收以逗号分隔的参数列表，列表以NULL指针作为结束标志
     *e 函数传递指定参数envp，允许改变子进程的环境，无后缀e时，子进程使用当前程序的环境
     */
    if(vfork()==0){
        printf("----------execle-----------\n");
        if(execle("/bin/ls", "ls", "-a",NULL,NULL )==-1){
            perror("execle error");
            exit(1);

        }
    }

    /**
     *创建子进程并调用execve
     * v 希望接收到一个以NULL结尾的字符串数组的指针
     * e 函数传递指定参数envp，允许改变子进程的环境，无后缀e时，子进程使用当前程序的环境
     */
    if(vfork()==0){
        printf("----------execv-----------\n");
        if(execve("/bin/ls",arg,NULL) ==-1){
            perror("execve error");
            exit(1);

        }
    }

    return 0;
}
