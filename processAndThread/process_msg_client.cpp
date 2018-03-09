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

    printf("Messages Queue- client key %d\n",key);

    if((msgid=msgget(key,IPC_CREAT|0777))< 0){
        perror("msgget error\n");
        exit(1);
    }

    printf("client msgid is %d\n", msgid);
    printf("client pid is %d\n", getpid());
    msgbuf.msgtype = 888;
    sprintf(msgbuf.msgtext,"I'm client %d",getpid());
    msgsnd(msgid, &msgbuf, sizeof(msgbuf.msgtext),0);

    msgrcv(msgid, &msgbuf, 256, 999, 0);
    printf("get messgages msgtype is %ld and msgtext is %s\n", msgbuf.msgtype,msgbuf.msgtext);
    return 0;
}

