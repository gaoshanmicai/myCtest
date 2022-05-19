#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define SIZE 1024

void printf_error(void *s)
{
        fprintf(stderr,"%s\n",(char *)s);
        exit(1);
}
int main(void)
{
        int shmid;
        key_t key;
        int ret;

        /* 创建key值 */
        key = ftok("../",2021);
        if(key==-1)
        {
                printf_error("ftok error");
        }
        system("ipcs -m");      //查看共享内存

        //打开共享内存
        shmid = shmget(key,SIZE,IPC_CREAT|0666);
        if(shmid<0)
        {
                printf("shmget error");
        }
        // 映射
        char *shmad = shmat(shmid,NULL,0);
        if(shmad<0)
        {
                printf_error("shmat error");
        }
        // 读取共享内存区数据
        printf("data = [%s]\n",shmad);
        //分离共享内存和当前进程
        ret = shmdt(shmad);
        if(ret<0)
        {
                printf_error("shmdt error");
        }
        printf("deleted shared_memory\n");
        //删除共享内存
        shmctl(shmid,IPC_RMID,NULL);
        system("ipcs -m");
        return 0;
}