#include<stdio.h>

int main()
{
    char fname[2][32]={0};
    char theLine[128] ={0};

    FILE *fp[2];

    puts("the input file name :\n");
   
    scanf("%s",fname[0]);
     getchar();
    printf("the input name is %s\n",fname[0]);

    puts("the output file name :\n");
    
    scanf("%s",fname[1]);
    getchar();
    printf("the output name is %s\n",fname[1]);

    //create the input file
    fp[0] =fopen(fname[0],"w+");
    if(fp[0]==NULL)
        perror("error open\n");

    fputs("nihaome",fp[0]);

    fclose(fp[0]);
    
    //create the input file
    fp[0] =fopen(fname[0],"r");
    if(fp[0]==NULL)
        perror("error open\n");

        fgets(theLine,128,fp[0]);

    //create the output file

     fp[1] =fopen(fname[1],"w+");
    if(fp[1]==NULL)
        perror("error open\n");


    fputs("the out put\n",fp[1]);

    fputs(theLine,fp[1]);




    



    fclose(fp[0]);

    fclose(fp[1]);


    return 0;





}