#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <semaphore.h>
#include <string>
#include <algorithm>

using namespace std;
sem_t sem;
sem_t sem_add;

string baby = "";

void *thread1(void *args){

    sem_wait(&sem);
    cout << "thread1 pid is:" << pthread_self() << endl;
    for(int i = 0;i<5;i++){
        transform(baby.begin(), baby.end(), baby.begin(),::toupper);
        cout << baby <<endl;
        sem_post(&sem_add);
        sem_wait(&sem);
    }
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    int ret = 0;;
    int error = 0;
    pthread_t pt1;

    sem_init(&sem, 0, 0);
    sem_init(&sem_add, 0, 1);
    //创建并启动一个线程(函数执行完后，新创建的线程已经启动,调用的线程也将继续执行(main));
    ret = pthread_create(&pt1, nullptr,  &thread1,nullptr);
    if(ret){
        cout << "Can't create thread1" << endl;
        sem_destroy(&sem);
        return 1;
    }

    sem_wait(&sem_add);
    for(int i = 0;i<5;i++){
        cout << "输入单词:" ;
        cin >> baby;
        sem_post(&sem);
        sem_wait(&sem_add);
    }
    sem_post(&sem);
    //main线程在这里阻塞，等待线程1执行完毕
    error = pthread_join(pt1,nullptr);
    if (error) {
        cout << "thread1 join error" << endl;
        sem_destroy(&sem);
        return 1;
    }

    //两个线程都执行完毕可以释放信号量
    sem_destroy(&sem);
    sem_destroy(&sem_add);
    return 0;

}
