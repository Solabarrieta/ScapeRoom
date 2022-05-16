#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int history(int args, char *argv[])
{
    char *buffer;
    char arg1[20] = "";
    char arg2[20] = "";
    char arg3[20] = "";

    //generate the bin folder path
    char *root_path;
    char home_dir[255];
    getcwd(home_dir, sizeof(home_dir));
    char *cut=strstr(home_dir,"/ScapeRoom");
    root_path = (char *)malloc(strlen(home_dir)+strlen("/ScapeRoom/bin/"));
    strncpy(root_path,home_dir,cut-home_dir);
    strcat(root_path,"/ScapeRoom/bin/");
    ////////////////////////////////////////////

    int fd = open("/home/k1/github_scaperoom/ScapeRoom/history_log.txt", O_RDWR | O_CREAT, 0777);
    lseek(fd, 0, SEEK_END);
    //printf("%s", argv[0]);

    if (args == 3)
    {
        buffer = (char *)malloc(strlen(argv[0])+strlen(argv[1]) +strlen(argv[2]) +strlen("  \n"));
        strcpy(arg1, argv[0]);
        strcpy(arg2, argv[1]);
        strcpy(arg3, argv[2]);
        strcat(buffer, arg1);
        strcat(buffer, " ");
        strcat(buffer, arg2);
        strcat(buffer, " ");
        strcat(buffer, arg3);
        strcat(buffer, "\n");
        //printf("%s", buffer);
    }
    else if (args == 2)
    {
        buffer = (char *)malloc(strlen(argv[0])+strlen(argv[1]) +strlen("  \n"));
        strcpy(arg1, argv[0]);
        strcpy(arg2, argv[1]);
        strcat(buffer, arg1);
        strcat(buffer, " ");
        strcat(buffer, arg2);
        strcat(buffer, "\n");
        //printf("%s", buffer);
    }
    else if (args == 1)
    {
        buffer = (char *)malloc(strlen(argv[0]) +strlen("  \n"));
        strcpy(arg1, argv[0]);
        strcat(buffer, arg1);
        strcat(buffer, "\n");
        //printf("%s", buffer);
    }

    buffer=buffer+strlen(root_path);

    write(fd, buffer, strlen(buffer));
    close(fd);
    return 0;
}