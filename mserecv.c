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
	int msgid;
	key_t key;
	int running = 1;
	struct msgcbuf data;
	memset(data.mtext,0,BUFFSIZE);
	long mtype=0;

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
	/* 从队列中获取消息，直到遇到end消息为止 */
	while(running)
	{
		if(msgrcv(msgid,(void *)&data,BUFFSIZE,mtype,0)==-1)
		{
			fprintf(stderr,"msgrcv error with errno：%d\n",errno);
			exit(1);
		}
		printf("message:%s\n",data.mtext);
	/* 删除消息队列 */
		if(strncmp(data.mtext,"end",3)==0)
		{
			if(msgctl(msgid,IPC_RMID,NULL)==0)
			{
				printf("delete message queue success!\n");
			}
			running =0;
		}
	}
	exit(0);
}