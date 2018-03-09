#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/msg.h>

#define MEG_FILE "./passwd"

typedef struct msgbuff{
    long msgtype;
    char msgtext[256];
}msgbuff;

int main(int argc, char *argv[])
{
    int msgid;
    key_t key;
    msgbuff msgbuf;

    if((key=ftok(MEG_FILE, 0))< 0){
        perror("ftok error\n");
        exit(1);
    }

    printf("Messages Queue- server key %d\n",key);

    if((msgid=msgget(key,IPC_CREAT|0777))< 0){
        perror("msgget error\n");
        exit(1);
    }

    printf("server msgid is %d\n", msgid);
    printf("server pid is %d\n", getpid());

    while(1){
        msgrcv(msgid, &msgbuf, 256, 888, 0);
        printf("get messgages msgtype is %ld and msgtext is %s\n", msgbuf.msgtype,msgbuf.msgtext);
        msgbuf.msgtype = 999;
        sprintf(msgbuf.msgtext,"I'm server %d",getpid());
        msgsnd(msgid, &msgbuf, sizeof(msgbuf.msgtext),0);
    }
    return 0;
}

