#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>


//function to check if the given file is a real file or directory
//return 0 if it's a directory
//else is not dir
int isDir(char *filename)
{
    struct stat info;
    stat(filename,&info);
    return S_ISREG(info.st_mode);
}

//function to check if cmd exists in cmd_list
int check_cmd(char *cmd, char *cmd_list[10])
{
    // int size= sizeof(cmd_list[0])/sizeof(cmd_list[0][0]);
    int i;
    for (i = 0; i < 10; i++)
    {
        if (strcmp(cmd, cmd_list[i]) == 0)
            return i;
    }
    return -1;
}
