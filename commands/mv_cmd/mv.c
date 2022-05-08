#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../../functions/useful_functions.c"


int mv(char *origin_file, char *destination)
{

    if(link(origin_file, destination)==0 && unlink(origin_file)==0)
        return 1;
    else{
        perror("ERROR : can't move \n");
        return 0;
    }

}
int main(int argc, char **argv)
{
    if (argc == 3)
    {
        //if file 1  exist
        if(access(argv[1],F_OK)==0)
        {

            printf("%s file exists \n ",argv[1]);
            //if it's a directory
            if(isDir(argv[2])==0)
            {
                if(opendir(argv[2]))
                {


                    printf("%s is a dir \n ",argv[2]);
                    char current_directory[256];
                    getcwd(current_directory, sizeof(current_directory));

                    strcat(current_directory,"/");
                    strcat(current_directory,argv[2]);
                    strcat(current_directory,"/");
                    strcat(current_directory,argv[1]);

                    mv(argv[1], current_directory);
                    return 1;

                }
                else
                {
                    rename(argv[1],argv[2]);
                    return 1;
                }
            }
            //if file exists
            else if(access(argv[2],F_OK)==0)
            {
                unlink(argv[2]);
                rename(argv[1],argv[2]);
                return 1;
            }

            else
            {
                write(1, "error in the number of arguments\n", strlen("error in the number of arguments\n"));
                return 0;
            }

        }
        else{
            write(1, "file 1 doesn't exist\n", strlen("file 1 doesn't exist\n"));
            return 0;
        }
    }
}
