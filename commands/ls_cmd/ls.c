
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include "../../.Global/global.h"
#include "../../functions/useful_functions.c"

void ls(char *path)
{
    // using the dirent library
    DIR *dir;
    struct dirent *ent;
    struct stat info;

    int k = 0;
    // open the folder in the path
    if ((dir = opendir(path)) != NULL)
    {
        write(1, "\n", strlen("\n"));

        // print all the files and directory within directory
        while ((ent = readdir(dir)) != NULL)
        {

            if (strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0)
            {
                stat(ent->d_name, &info);
                if (!S_ISREG(info.st_mode))
                {
                    printf("\033[0;34m");
                    printf("%s", ent->d_name);
                    // printf("\033[0;37m");
                }
                else
                {
                    printf("\033[0m%s  ", ent->d_name);
                    //  printf("%s", ent->d_name);
                    // write(0, ent->d_name, strlen(ent->d_name));
                }
                printf(" ");
                printf(" ");
                printf("\033[0m");

                // write(0, ent->d_name, strlen(ent->d_name));
            }

            k++;
        }
        printf("\n");
        printf("\n");
        closedir(dir);
    }
    else if (errno == ENOENT)
    {
        // if the file is not opened
        write(1, "Path not found\n", strlen("Path not found\n"));
    }
    else
    {
        write(1, "error while reading this directory\n", strlen("error while reading this directory\n"));
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        ls(".");
    }
    else if (argc == 2)
    {

        ls(argv[1]);
    }
    else
    {
        write(1, "error ls should have one or no arguments\n", strlen("error ls should have one or no arguments\n"));
        return 1;
    }

    return 0;
}
