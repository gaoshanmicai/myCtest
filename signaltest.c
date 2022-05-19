#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define N 10
#define true 1

void show_buffer();
void *producer(void *id);
void *consumer(void *id);

typedef int item;
//环形队列
int in =0, out =0;
//缓冲区
item buffer[N];
//互斥、空缓冲区、满缓冲区信号量
sem_t mutex,empty,full;

/* 生产者 */
void *producer(void *id)
{
	while(true)
	{
		item nextp = rand() % 10;
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in]=nextp;
		in = (++in)%N;
		printf("======%s======\n",(char *)id);
		printf("生产了:%d\n",nextp);
		show_buffer();
		sem_post(&mutex);
		sem_post(&full);
	}
}

/* 消费者 */
void *consumer(void *id)
{
	while(true)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		item nextc = buffer[out];
		out = (++out)%N;
		int emp,ful;
		sem_getvalue(&empty,&emp);
		sem_getvalue(&full,&ful);
		printf("======%s======\n"
				"缓冲区大小：%d\n"
				"消费的物品：%d\n"
				"空缓冲区的数量：%d\n"
				"满缓冲区的数量：%d\n"
				,(char*)id,N,nextc,emp,ful);
		show_buffer();
		sem_post(&mutex);
		sem_post(&empty);
	}
}

/* 显示缓冲区内容 */
void show_buffer()
{
	printf("[ ");
	if(in==out)//满
		for(int i=0;i<N;i++)
			printf("%2d ",buffer[i]);
	else if(out<in)
		for(int i=out ;(i%N)<in;i++)
			printf("2%d ",buffer[i]);
	else
	{
		for(int i=out;i<N;i++)
			printf("%2d ",buffer[i]);
		for(int i=0;i<in;i++)
			printf("%2d ",buffer[i]);
	}
	printf("]\n");
}

int main(void)
{
	/*初始化信号量*/
	if(sem_init(&mutex,0,1)==-1)
		perror("sem_init");
	if(sem_init(&empty,0,N)==-1)
		perror("sem_init");
	if(sem_init(&full,0,0)==-1)
		perror("sem_init");
	/* 两个生产者、两个消费者 */
	pthread_t p1,p2,c1,c2;
	int ret;
	if((ret=pthread_create(&p1,NULL,producer,(void *)"生产者1"))!=0)
	{
		fprintf(stderr,"ptheard_create error,error number :%d\n",ret);
		exit(1);
	}
	if((ret=pthread_create(&p2,NULL,producer,(void *)"生产者2"))!=0)
        {
                fprintf(stderr,"ptheard_create error,error number :%d\n",ret);
                exit(1);
        }
	if((ret=pthread_create(&c1,NULL,consumer,(void *)"消费者1"))!=0)
        {
                fprintf(stderr,"ptheard_create error,error number :%d\n",ret);
                exit(1);
        }
	if((ret=pthread_create(&c2,NULL,consumer,(void *)"消费者2"))!=0)
        {
                fprintf(stderr,"ptheard_create error,error number :%d\n",ret);
                exit(1);
        }
	if(ret=pthread_join(p1,NULL))
	{
		 fprintf(stderr,"ptheard_join error,error number :%d\n",ret);
                exit(1);
	}
	if(ret=pthread_join(p2,NULL))
        {
                 fprintf(stderr,"ptheard_join error,error number :%d\n",ret);
                exit(1);
        }
	if(ret=pthread_join(c1,NULL))
        {
                 fprintf(stderr,"ptheard_join error,error number :%d\n",ret);
                exit(1);
        }
	if(ret=pthread_join(c2,NULL))
        {
                 fprintf(stderr,"ptheard_join error,error number :%d\n",ret);
                exit(1);
        }
	return 0;



}
