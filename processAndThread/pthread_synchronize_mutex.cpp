#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int baby;

void *thread1(void *args){

    cout << "thread1 pid is:" << pthread_self() << endl;
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        baby++;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return nullptr;


}
void *thread2(void *args){

    cout << "thread2 pid is:" << pthread_self() << endl;
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        cout << "baby is:" << baby  << endl;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return nullptr;

}

int main(int argc, char *argv[])
{
    int ret = 0;;
    int error = 0;
    pthread_t pt1,pt2;
    baby = 0;

    //创建并启动一个线程(函数执行完后，新创建的线程已经启动,调用的线程也将继续执行(main));
    ret = pthread_create(&pt1, nullptr,  &thread1,nullptr);
    if(ret){
        cout << "Can't create thread1" << endl;
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    //创建并启动一个线程(函数执行完后，新创建的线程已经启动,调用的线程也将继续执行(main));
    ret = pthread_create(&pt2, nullptr,  &thread2,nullptr);
    if(ret){
        cout << "Can't create thread2" << endl;
        pthread_mutex_destroy(&mutex);
        return 1;
    }
    //main线程在这里阻塞，等待线程1执行完毕
    error = pthread_join(pt1,nullptr);
    if (error) {
        cout << "thread1 join error" << endl;
        pthread_mutex_destroy(&mutex);
        return 1;
    }
    //main线程在这里阻塞，等待线程2执行完毕
    error =  pthread_join(pt2,nullptr);
    if (error) {
        cout << "thread2 join error" << endl;
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    //两个线程都执行完毕可以释放信号量
    pthread_mutex_destroy(&mutex);
    return 0;

}
