#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};


int sem_init(int sem_id,int val){
    union semun temp;
    temp.val = val;
    if(semctl(sem_id, 0, SETVAL,  temp )==-1){
        perror("init sem error!\n");
        return 1;
    }
    return 0;
}

int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = -1;
    sbuf.sem_flg = SEM_UNDO;
    if(semop(sem_id, &sbuf, 1)==-1){
        perror("sem_p perror\n");
        return 1;
    }
    return 0;
}

// P操作:
//    若信号量值为1，获取资源并将信号量值-1
//    若信号量值为0，进程挂起等待
int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = 1;
    sbuf.sem_flg = SEM_UNDO;
    if(semop(sem_id, &sbuf, 1)==-1){
        perror("sem_p error\n");
        return 1;
    }
    return 0;
}

// V操作：
//    释放资源并将信号量值+1
//    如果有进程正在挂起等待，则唤醒它们
int del_sem(int sem_id){
    union semun temp;
    if (semctl(sem_id,0,IPC_RMID,  temp)==-1) {
        perror("del_em error\n");
        return 0;
        
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int sem_id;
    key_t key;
    pid_t pid;

    if ((key=ftok("./passwd",0))<0) {
        perror("key get error\n");
        exit(1);
    }

    if((sem_id=semget(key, 1, IPC_CREAT|0666))<0){
        perror("sem_id get error\n");
        exit(1);
    }

    
    sem_init(sem_id,0);
    pid = fork();
    if (pid<0) {
        perror("fork error!\n");
        exit(1);
    }else if(pid==0){
        sleep(2);
        printf("child pid is %d\n",getpid());
        sem_v(sem_id);
    }else{
        sem_p(sem_id);
        printf("father pid is %d\n",getpid());
        sem_v(sem_id);
        del_sem(sem_id);
    }

    return 0;

}
