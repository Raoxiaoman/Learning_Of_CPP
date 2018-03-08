#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <semaphore.h>
#include <list>

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

size_t LIST_SIZE = 10;
list<int> lists;

void *producer(void *args){
    for (size_t i = 0; i < LIST_SIZE; ++i) {
        pthread_mutex_lock(&mutex);
        while(lists.size() > LIST_SIZE){
            pthread_cond_wait(&empty, &mutex);
        }
        lists.push_back(i);
        cout << pthread_self() << "_producer:" << i << endl;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    
    }
    pthread_exit(0);
}

void *consumer(void *args){
    int pop = 0;
    for (size_t i = 0; i < LIST_SIZE; ++i) {
        pthread_mutex_lock(&mutex);
        while(lists.size() < 1){
            pthread_cond_wait(&full, &mutex);
        }
        pop = lists.front();
        lists.pop_front();
        cout << pthread_self() << "_comsumer:" << pop << endl;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
    pthread_exit(0);

    
}

int main(int argc, char *argv[])
{
    int ret = 0;;
    int error = 0;
    pthread_t pt1,pt2;

    ret = pthread_create(&pt1, nullptr,  &producer,nullptr);
    if(ret){
        cout << "Can't create thread1" << endl;
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&full);
        pthread_cond_destroy(&empty);
        return 1;
    }

    ret = pthread_create(&pt2, nullptr,  &consumer,nullptr);
    if(ret){
        cout << "Can't create thread2" << endl;
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&full);
        pthread_cond_destroy(&empty);
        return 1;
    }


    error = pthread_join(pt1,nullptr);
    if (error) {
        cout << "thread1 join error" << endl;
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&full);
        pthread_cond_destroy(&empty);
        return 1;
    }
    error =  pthread_join(pt2,nullptr);
    if (error) {
        cout << "thread2 join error" << endl;
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&full);
        pthread_cond_destroy(&empty);
        return 1;
    }

    //两个线程都执行完毕可以释放信号量
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    return 0;

}
