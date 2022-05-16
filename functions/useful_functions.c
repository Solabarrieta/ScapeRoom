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
int check_cmd(char *cmd, char *cmd_list[9])
{
    // int size= sizeof(cmd_list[0])/sizeof(cmd_list[0][0]);
    int i;
    for (i = 0; i < 9; i++)
    {
        if (strcmp(cmd, cmd_list[i]) == 0)
            return i;
    }
    return -1;
}

//function to check if a file exists in Inventory
int isinInventeroy(char *filename)
{
    char *file_path;

    char home_dir[255];

    getcwd(home_dir, sizeof(home_dir));
    char *cut=strstr(home_dir,"/ScapeRoom");

    file_path = (char *)malloc(strlen(home_dir) + strlen("/.inventory/")+ strlen(filename));

    strncpy(file_path,home_dir,cut-home_dir);
    strcat(file_path, "/ScapeRoom/.inventory/");
    strcat(file_path, filename);

    FILE *file;
    file=fopen(file_path,"r");

    if(file)
    {
        //printf("Object exists in Inventory\n");
        fclose(file);
    return 1;
    }
    else{
        //printf("You don't have the necessary object to enter this room\n");
        return 0;
    }

}
//function to get the root path of the game
char *getRootPath()
{
    char home_dir[255];
    char *root_path;

    getcwd(home_dir, sizeof(home_dir));
    char *cut=strstr(home_dir,"/ScapeRoom");

    root_path = (char *)malloc(strlen(home_dir) + strlen("/ScapeRoom/")-strlen(cut));

    strncpy(root_path,home_dir,cut-home_dir);

    strcat(root_path, "/ScapeRoom/");

    return root_path;
}
/*
int check_pipe(char *cmd_list[])
{
    int size= sizeof(cmd_list[0])/sizeof(cmd_list[0][0]);
    int i;
    for (i = 0; i < 10; i++)
    {
        if (strcmp("|", cmd_list[i]) == 0)
            return i;
    }
    return -1;
}*/





