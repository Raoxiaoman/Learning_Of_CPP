/*
 *
读写锁：
     读写锁和互斥量类似，不过读写锁允许更高的并行性。互斥量有两种状态，要么加锁，要么解锁，而且两种状态一次只能有一个线程进行访问。读写锁有 3 中状态，读模式下加锁，写模式下加锁，不加锁装填。一次只能有一个线程可以占有写模式下的读写锁，但是有多个进程可以同时占有写模式下的读写锁

适用场景：
     读写锁非常适用于对数据结构的读次数远大于写次数的情况。 
 *
 * */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

int baby;

void *Reader(void *args){

    for (int i = 0; i < 10; ++i) {
        pthread_rwlock_rdlock(&rwlock);
        cout << pthread_self() << "_print:" << baby << endl;
        pthread_rwlock_unlock(&rwlock);
        sleep(2);
    }
    
    return nullptr;


}
void *Writer(void *args){

    for (int i = 0; i < 10; ++i) {
        pthread_rwlock_wrlock(&rwlock);
        baby++;
        cout << "baby++" << endl;
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
    return nullptr;

}

int main(int argc, char *argv[])
{
    int ret = 0;;
    int error = 0;
    pthread_t pt1,pt2,pt3;
    baby = 0;

    ret = pthread_create(&pt1, nullptr,  &Reader,nullptr);
    if(ret){
        cout << "Can't create thread1" << endl;
        pthread_rwlock_destroy(&rwlock);
        return 1;
    }
    ret = pthread_create(&pt2, nullptr,  &Reader,nullptr);
    if(ret){
        cout << "Can't create thread2" << endl;
        pthread_rwlock_destroy(&rwlock);
        return 1;
    }

    ret = pthread_create(&pt3, nullptr,  &Writer,nullptr);
    if(ret){
        cout << "Can't create thread3" << endl;
        pthread_rwlock_destroy(&rwlock);
        return 1;
    }
    error = pthread_join(pt1,nullptr);
    if (error) {
        cout << "thread1 join error" << endl;
        pthread_rwlock_destroy(&rwlock);
        return 1;
    }
    error =  pthread_join(pt2,nullptr);
    if (error) {
        cout << "thread2 join error" << endl;
        pthread_rwlock_destroy(&rwlock);
        return 1;
    }
    error =  pthread_join(pt3,nullptr);
    if (error) {
        cout << "thread3 join error" << endl;
        pthread_rwlock_destroy(&rwlock);
        return 1;
    }

    //线程都执行完毕可以释放信号量
    pthread_rwlock_destroy(&rwlock);
    return 0;

}
