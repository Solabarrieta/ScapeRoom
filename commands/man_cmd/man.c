#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "../../functions/useful_functions.c"

void man(char *cmd_name)
{
    char *cmd_list[11] = {"pwd", "cp", "ls", "cat", "exit", "mv", "Jarvis", "grep", "man","push","wc"};
    int cmd_num;
    char *manual_path;

    char home_dir[255];

    getcwd(home_dir, sizeof(home_dir));
    char *cut = strstr(home_dir, "/ScapeRoom");

    manual_path = (char *)malloc(strlen(home_dir) + strlen(cmd_list[cmd_num]) + strlen("/Docs/"));

    strncpy(manual_path, home_dir, cut - home_dir);
    strcat(manual_path, "/ScapeRoom/Docs/");

    if (strcmp(cmd_name, "cd") == 0)
    {
        strcat(manual_path, "cd");

        printScript(manual_path);
    }
    else
        cmd_num = check_cmd(cmd_name, cmd_list);
    if (cmd_num != -1 && strcmp(cmd_name, "cd") != 0)
    {

        strcat(manual_path, cmd_list[cmd_num]);

        printScript(manual_path);
    }
    else if (cmd_num == -1)
        write(1, "Comand entred for man not Found \n ", strlen("Comand entred for man not Found \n "));
}

int main(int argc, char *argv[])
{

    if (argc == 2)
    {

        man(argv[1]);
    }
    else
    {
        write(1, "error man should have one arguments\n", strlen("error man should have one arguments\n"));
        return 1;
    }

    return 0;
}
