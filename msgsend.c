#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgbuf.h"

int main(void)
{
	int running = 1;
	struct msgcbuf data;
	long mtype=0;
	key_t key;	
	int msgid;

	/* 创建消息队列 */
	key = ftok("./",2);
        if(key==-1)
        {
                printf("ftok error\n");
                exit(1);
        }

        /* 建立消息队列 */
        msgid=msgget(key,IPC_CREAT|0666);
        if(msgid==-1)
        {
                fprintf(stderr,"msgget error");
                exit(1);
        }
	  /* 发送数据 */
	while(running)
	{
		printf("enter some test:");
		fgets(data.mtext,BUFFSIZE ,stdin);
		data.mtype = 1;
		if(msgsnd(msgid,(void *)&data,BUFFSIZE,0)==-1)
		{
			fprintf(stderr,"msgsnd error\n");
			exit(1);
		}
		if(strncmp(data.mtext,"end",3)==0)
		{
			running = 0;
		}
	}
	exit(0);
}