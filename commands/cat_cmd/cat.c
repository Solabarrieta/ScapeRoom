#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

void cat(char filename[50])
{
    //file descriptor : open file in read mode
   int fd= open(filename, O_RDONLY);
   char *c;
   //size_t is the size of an alloctaed block in memory
   ssize_t bytestoread;

    if(fd != -1)
    {

        do{

            bytestoread=read(fd,c,1);
            write(1,c,strlen(c));

        }while(bytestoread>0);
    }
   else if(errno==ENOENT)
    write(1,"File does not exist\n",strlen("File does not exist\n"));
   /*else if(errno!=ENOTDIR)
   {
       write(1,filename,strlen(filename));
       write(1,": is not a file\n",strlen(": is not a file\n"));
   }*/

    close(fd);
}
int main(int argc, char *argv[])
{

    if (argc==2)
    {

        cat(argv[1]);
    }
    else
    {
        write(1,"error cat should have one arguments\n",strlen("error cat should have one arguments\n"));
        return 1;
    }


    return 0;
}
