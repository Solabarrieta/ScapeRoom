#include <dirent.h>
// Error control.
#include <errno.h>
// System flags.
#include <sys/fcntl.h>
// Stat!
#include <sys/stat.h>
// Stdlib util
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int mv(char *origin_file, char *destination)
{
    int i,fd1,fd2;
    char* buffer[2];
    //i=link((const char *)origin_file, (const char *)destination);
    fd1=open(origin_file,O_RDONLY);
    fd2=open(destination,O_WRONLY);
    if(fd2== -1)
    fd2 =creat(destination,0666);
    //rename((const char *)fd1,(const char *)fd2);

    while(i=read(fd1,buffer,1)>0)
    {
        write(fd2,buffer,1);

    }
    rename((const char *)origin_file,(const char *)destination);
    //unlink((const char *)origin_file);
        close(fd1);
        close(fd2);
    //if(errno==EEXIST)
      //  printf("\n ACCESS ERROR \n");


    return 1;
    /*if(i!=0 || j!=0)
        return -1;
    else return 1;*/
}

int main(int argc, char *argv[])
{
    //char *err_sys = THE_SYSTEM;
    //char *glinda = GLINDA;

    if (argc != 3)
    {
        // If the command is used incorrectly, it will teach the user how to use it.
        //printerr("HAHAHAHAHAHA, useless ape!", err_sys);
        write(1, "My dear sweet child, do <<mv file.txt new_location>>, please :)\n",strlen("My dear sweet child, do <<mv file.txt new_location>>, please :)\n"));

        return 1;
    }
    if (mv(argv[1], argv[2])==-1)
    {
        // If there is no directory to reach,
        //printerr("I cannot reach that place, ape. Move on!", err_sys);
        write(1,"I cannot move there!\n", strlen("I cannot move there!\n"));

        return 1;
    }

    return 0;
}
