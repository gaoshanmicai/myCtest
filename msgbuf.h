#ifndef _MSG_BUFF_H
#define _MSG_BUFF_H
#include <errno.h>

#define BUFFSIZE 1024


struct msgcbuf{
	long mtype;
	char mtext[BUFFSIZE];
};


#endif