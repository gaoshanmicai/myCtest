#include <stdio.h>
#include <string.h>



int main(void)
{
    char putstr[80]={0};
    char mydata;


    // input a string 
    while((mydata=getchar())!='\0')
    {
       putchar(mydata);
    }

    return 0;
}