
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

void ls(char path[50])
{
    //using the dirent library
    DIR *dir;
    struct dirent *ent;

    int k=0;
    //open the folder in the path
    if( (dir=opendir(path))!=NULL )
    {
        //print all the files and directory within directory
        while( (ent=readdir(dir)) != NULL)
        {
            write(1,"\n",2);
            if(strcmp(ent->d_name,"..")!=0 && strcmp(ent->d_name,".")!=0 )
            {
                //write(1,"\n",2);
                //write(1,"\t",2);
                write(1,ent->d_name,strlen(ent->d_name));
            }

            k++;
        }
        write(1,"\n",2);
        closedir(dir);
    }
    else if(errno == ENOENT)
    {
        //if the file is not opened
        write(1,"Path not found\n",strlen("Path not found\n"));
    }
    else
    {
         write(1,"error while reading this directory\n",strlen("error while reading this directory\n"));
    }

}

int main(int argc, char *argv[])
{
    if(argc==1)
    {
        ls(".");

    }
    else if (argc==2)
    {

        ls(argv[1]);
    }
    else
    {
        write(1,"error ls should have one or no arguments\n",strlen("error ls should have one or no arguments\n"));
        return 1;
    }


    return 0;
}

