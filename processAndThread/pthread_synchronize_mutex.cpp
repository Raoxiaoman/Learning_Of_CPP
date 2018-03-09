/*
 *
通过锁机制实现线程间的同步。同一时刻只允许一个线程执行一个关键部分的代码。
方法有 :
int pthread_mutex_init(pthread_mutex_t *mutex,const pthread_mutex_attr_t *mutexattr);
int pthread_mutex_lock(pthread_mutex *mutex);
int pthread_mutex_destroy(pthread_mutex *mutex);
int pthread_mutex_unlock(pthread_mutex *);

(1) 先初始化锁 init() 或静态赋值 pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIER
attr_t 有:

PTHREAD_MUTEX_TIMED_NP: 其余线程等待队列
PTHREAD_MUTEX_RECURSIVE_NP: 嵌套锁, 允许线程多次加锁, 不同线程, 解锁后重新竞争
PTHREAD_MUTEX_ERRORCHECK_NP: 检错, 与一同, 线程请求已用锁, 返回 EDEADLK;
PTHREAD_MUTEX_ADAPTIVE_NP: 适应锁, 解锁后重新竞争

(2) 加锁, lock,trylock,lock 阻塞等待锁, trylock 立即返回 EBUSY

(3) 解锁, unlock 需满足是加锁状态, 且由加锁线程解锁

(4) 清除锁, destroy(此时锁必需 unlock, 否则返回 EBUSY,Linux 下互斥锁不占用内存资源)
 *
 * */
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
