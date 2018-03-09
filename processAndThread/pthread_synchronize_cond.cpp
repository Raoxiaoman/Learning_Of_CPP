/*
 *
条件变量（cond）
    利用线程间共享的全局变量进行同步的一种机制。条件变量上的基本操作有：触发条件 (当条件变为 true 时)；等待条件，挂起线程直到其他线程触发条件。
方法有：
    int pthread_cond_init(pthread_cond_t *cond,pthread_condattr_t *cond_attr);
    int pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex);
    int pthread_cond_timewait(pthread_cond_t *cond,pthread_mutex *mutex,const timespec *abstime);
    int pthread_cond_destroy(pthread_cond_t *cond);
    int pthread_cond_signal(pthread_cond_t *cond);
    int pthread_cond_broadcast(pthread_cond_t *cond);  // 解除所有线程的阻塞
特点有
    (1)pthread_cond_wait 自动解锁互斥量 (如同执行了 pthread_unlock_mutex)，并等待条件变量触发。这时线程挂起，不占用 CPU 时间，直到条件变量被触发（变量为 ture）。在调用 pthread_cond_wait 之前，应用程序必须加锁互斥量。pthread_cond_wait 函数返回前，自动重新对互斥量加锁 (如同执行了 pthread_lock_mutex)。

    (2) 互斥量的解锁和在条件变量上挂起都是自动进行的。因此，在条件变量被触发前，如果所有的线程都要对互斥量加锁，这种机制可保证在线程加锁互斥量和进入等待条件变量期间，条件变量不被触发。条件变量要和互斥量相联结，以避免出现条件竞争——个线程预备等待一个条件变量，当它在真正进入等待之前，另一个线程恰好触发了该条件（条件满足信号有可能在测试条件和调用 pthread_cond_wait 函数（block）之间被发出，从而造成无限制的等待）。

    (3)pthread_cond_timedwait 和 pthread_cond_wait 一样，自动解锁互斥量及等待条件变量，但它还限定了等待时间。如果在 abstime 指定的时间内 cond 未触发，互斥量 mutex 被重新加锁，且 pthread_cond_timedwait 返回错误 ETIMEDOUT。abstime 参数指定一个绝对时间，时间原点与 time 和 gettimeofday 相同：abstime = 0 表示 1970 年 1 月 1 日 00:00:00 GMT。

    (4)pthread_cond_destroy 销毁一个条件变量，释放它拥有的资源。进入 pthread_cond_destroy 之前，必须没有在该条件变量上等待的线程。

    (5) 条件变量函数不是异步信号安全的，不应当在信号处理程序中进行调用。特别要注意，如果在信号处理程序中调用 pthread_cond_signal 或 pthread_cond_boardcast 函数，可能导致调用线程死锁。
 * 
 * */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int BABY_MAX = 10;

int baby;

void *add_baby(void *args){

    cout << "add_baby pid is:" << pthread_self() << endl;
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        baby++;
        cout << "baby:" <<baby << endl;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(0);
}

void *watch_baby(void *args){
    cout << "watch pid is:" << pthread_self() << endl;
    pthread_mutex_lock(&mutex);
    //pthread_cond_wait()在条件检查的循环中，每次被signal后,检查条件是否满足(baby >= BABY_MAX)。
    while(baby < BABY_MAX){
        cout << "baby" <<baby <<"<" << BABY_MAX << endl;
        sleep(2);
        pthread_cond_wait(&cond, &mutex);
        cout << "watch is signaled:" << endl;
    }
    baby+=100;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);

}

int main(int argc, char *argv[])
{
    int ret = 0;;
    int error = 0;
    pthread_t pt1,pt2,pt3;
    baby = 0;

    ret = pthread_create(&pt1, nullptr,  &add_baby,nullptr);
    if(ret){
        cout << "Can't create thread1" << endl;
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    ret = pthread_create(&pt2, nullptr,  &add_baby,nullptr);
    if(ret){
        cout << "Can't create thread2" << endl;
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    ret = pthread_create(&pt3, nullptr,  &watch_baby,nullptr);
    if(ret){
        cout << "Can't create thread3" << endl;
        pthread_mutex_destroy(&mutex);
        return 1;
    }

    error = pthread_join(pt1,nullptr);
    if (error) {
        cout << "thread1 join error" << endl;
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        return 1;
    }
    error =  pthread_join(pt2,nullptr);
    if (error) {
        cout << "thread2 join error" << endl;
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        return 1;
    }
    error =  pthread_join(pt3,nullptr);
    if (error) {
        cout << "thread3 join error" << endl;
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        return 1;
    }

    //两个线程都执行完毕可以释放信号量
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;

}
