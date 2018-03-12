#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <cstring>

struct  msgbufs{
    long msgtype;
    char msgtext;
};

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

// P操作:
//    若信号量值为1，获取资源并将信号量值-1
//    若信号量值为0，进程挂起等待
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

// V操作：
//    释放资源并将信号量值+1
//    如果有进程正在挂起等待，则唤醒它们
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

int del_sem(int sem_id){
    union semun temp;
    if (semctl(sem_id,0,IPC_RMID,  temp)==-1) {
        perror("del_em error\n");
        return 0;
        
    }
    return 0;
}

int create_sem(key_t key){
    int sem_id;
    if((sem_id=semget(key, 1, IPC_CREAT|0666))<0){
        perror("sem_id get error\n");
        exit(1);
    }

    sem_init(sem_id,1);
    return sem_id;

}

int main(int argc, char *argv[])
{
    int sem_id,msg_id,shm_id;
    key_t key;
    if ((key=ftok("./passwd",0))<0) {
        perror("key get error\n");
        exit(1);
    }

    if((shm_id=shmget(key, 1024, IPC_CREAT|0666))<0){
        perror("shm_id get error\n");
        exit(1);
    }

    char *shm = static_cast<char *>(shmat(shm_id, 0, 0));

    if((msg_id=msgget(key,  IPC_CREAT|0777))<0){
        perror("msg_id get error\n");
        exit(1);
    }

    sem_id = create_sem(key);

    struct msgbufs msg;
    while(1){
        msgrcv(msg_id, &msg, 1, 888, 0);
        if(msg.msgtext =='q'){
            break;
        }else if(msg.msgtext =='r'){
            sem_p(sem_id);
            printf("%s\n", shm);
            sem_v(sem_id);
        }
    }
    shmdt(shm);
    struct shmid_ds buf1;
    struct msqid_ds buf2;
    shmctl(shm_id, IPC_RMID, &buf1);
    msgctl(msg_id, IPC_CREAT, &buf2);
    del_sem(sem_id);
    return 0;
}
