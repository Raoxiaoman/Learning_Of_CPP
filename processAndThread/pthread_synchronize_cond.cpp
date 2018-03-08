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
