#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

void remove_history_file()
{

    if (access("/home/k1/github_scaperoom/ScapeRoom/history_log.txt", F_OK) == 0)
    {
        // file exists
        char *argv[20] = {
        "rm",
        "-r",
        "/home/k1/github_scaperoom/ScapeRoom/history_log.txt"};
        int status;
        int pid = fork();
        if (pid == 0)
        {
            execvp("rm", argv);
        }

        while (wait(&status) != -1 || errno != ECHILD)
            ;


    }

    if (access("/home/k1/github_scaperoom/ScapeRoom/history_log.txt", F_OK) != 0)
    {
        // file doesn't exist
        int fd = open("/home/k1/github_scaperoom/ScapeRoom/history_log.txt", O_RDWR | O_CREAT, 0777);
    }
}
