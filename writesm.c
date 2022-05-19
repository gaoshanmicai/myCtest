#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

#define SIZE 1024

void printf_error(void *s)
{
        fprintf(stderr,"%s\n",(char *)s);
        exit(1);
}

int main(void)
{
        key_t key;
        int shmid;
        int ret;
        /*创建key值 */
        key = ftok("../",2021);
        if(key==-1)
        {
                printf_error("ftok error");
        }

        /* 创建共享内存 */
        shmid = shmget(key,SIZE ,IPC_CREAT|0666);
        if(shmid==-1)
        {
                printf_error("shmget error");
        }
        /* 映射 */
        char *shmad = shmat(shmid,NULL,0);
        if(shmad < 0)
        {
                printf_error("shmat error");
        }
        /* 拷贝数据至共享内存区 */
        memset(shmad,0,SIZE);
        strcpy(shmad,"How are you,mike\n");
        return 0;
}