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
