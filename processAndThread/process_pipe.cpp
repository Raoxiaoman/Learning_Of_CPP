#include <iostream>
#include <stdio.h>
#include <unistd.h>


char temp[] = "hello world";
using namespace std;
int main(int argc, char *argv[])
{
    int fd[2];
    int chlid = 0;
    char buff[20];
    if(pipe(fd)<0){
        cout << "create pipe error" << endl; 
    }

    chlid = fork();
    if(chlid < 0){
        cout << "create child process error" << endl; 
    }else if(chlid > 0){
        cout << "father" << endl;
        write(fd[1],temp,sizeof(temp));

    }else{
        cout << "child" << endl;
        read(fd[0],buff,sizeof(temp));
        cout << buff << endl;
    }



    return 0;
}
