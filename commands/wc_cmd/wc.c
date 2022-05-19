#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

 void wc(char *filename)
{
    int countC = 0;
   int countW = 0;
   int countL = 0;
   char ch;

    FILE *fp;

     fp = fopen(filename,"r");
    if(fp == NULL)
    {
        printf("File not found\n");
    }
    else{

       while((ch=fgetc(fp))!=EOF)
       {
           countC++;
           if(ch == ' ')
           {

                 countW++;
           }
           if(ch == '\n')
           {
                countL++;
           }
       }
       printf("number of character = %d\n",countC);
       printf("number of words  = %d\n",countW+1);
       printf("number of lines = %d\n",countL);
    }

}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        wc(argv[1]);
        return 1;
    }
    else
    {
        write(1,"wc should have one argument(file name)\n",strlen("wc should have one argument(file name)\n"));
        return 0;
    }

}






























