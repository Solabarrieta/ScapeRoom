#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include "../.Global/global.h"

int removeMain()
{

    char *argv[20] = {
        "rm",
        "-r",
        OIER_HOME};
    int status;
    int pid = fork();
    if (pid == 0)
    {
        execvp("rm", argv);
    }

    while (wait(&status) != -1 || errno != ECHILD)
        ;

    // char path[256];
    // getcwd(path, sizeof(path));
    // write(1, path, strlen(path));
    if (access("../Egypt", F_OK) == 0)
    {
        // file exists
        return 1;
    }
    else
    {
        // file doesn't exist
        return 0;
    }
}

/*int main(int argc, char *argv[])
{
    if (removeMain())
    {
        printf("Couldnt remove the folder!");
    }
    else
    {
        printf("Folder deleted correctly!");
    }
    return 0;
}*/