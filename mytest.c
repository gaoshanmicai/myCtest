#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    for(int i=0; i< 5;i++)
    {
        sleep(i);
        printf("stop %d second\n",i);
        fflush(stdout);
    }
    exit(0);
    //return 0;
}