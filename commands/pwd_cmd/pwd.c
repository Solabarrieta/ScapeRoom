#include <unistd.h>
#include <stdio.h>
#include <string.h>

void pwd()
{
    char current_directory[256];
    getcwd(current_directory,sizeof(current_directory));

    write(1,"you are in : ",12);

    write(1,current_directory,strlen(current_directory));
    write(1,"\n",2);



}

int main(int argc, char *argv[])
{
    if(argc==1)
    {
         pwd();

    }
    else
    {
        write(1,"Error : pwd has no arguments\n",30);
        return 1;
    }
}
