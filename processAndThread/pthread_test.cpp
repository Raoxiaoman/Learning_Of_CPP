#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct Args{
    int i;
    char * s;
    
}Args;

static int ha = 100;
void* thread1(void*arg){
    int i;
    int *ret = new int (0);
    if(arg==NULL){
        *ret = 1;
        return (void*)ret;
    }
    printf("ha:%d\n",ha);
    printf("thread1 pid is %d\n",(unsigned int)pthread_self());
    printf("process pid is %d\n",getpid());
    Args *args = static_cast<Args*>(arg);
    for (i = 0; i < 5; ++i) {
        printf("this is thread1,i:%d,s:%s\n",args->i,args->s);
        sleep(1);
    }
    return (void*)ret;
}


void* thread2(void*arg)
{   
    int i;
    int *ret = new int (0);
    if(arg==NULL){
        *ret = 1;
        return (void*)ret;
    }
    printf("ha:%d\n",ha);
    printf("thread1 pid is %u\n",(unsigned int)pthread_self());
    printf("process pid is %d\n",getpid());
    Args *args = static_cast<Args*>(arg);
    for (i = 0; i < 5; ++i) {
        printf("this is thread2,i:%d,s:%s\n",args->i,args->s);
        sleep(1);
    }
    return (void*)ret;

}

int main(int argc, char *argv[])
{
    int ret = 0;
    void *temp = NULL;
    char ss[] = "raohui";
    int error = 0;
    ha++;
    Args *arg = new Args;
    arg->i = 10;
    arg->s = ss;

    pthread_t pt1;
    pthread_t pt2;

    ret = pthread_create(&pt1, NULL, thread1, static_cast<void*>(arg));
    if(ret){

        printf("Can't Create thread1\n");
        return 1;
    }
    ret = pthread_create(&pt2, NULL, thread2, static_cast<void*>(arg));
    if(ret){

        printf("Can't Create thread2\n");
        return 1;
    }
    error = pthread_join(pt1, &temp);
    if (error) {
        printf("thread1 exit error\n");
        printf("thread1 exit code %d\n",*static_cast<int*>(temp));
        return -1;
    }
    printf("thread1 exit code %d\n",*static_cast<int*>(temp));
    error = pthread_join(pt2, &temp);

    if (error) {
        printf("thread2 exit error\n");
        printf("thread1 exit code %d\n",*static_cast<int*>(temp));
        return -1;
    }

    printf("thread1 exit code %d\n",*static_cast<int*>(temp));
    return 0;
}
