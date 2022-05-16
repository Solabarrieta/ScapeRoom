// myShell0
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include ".Global/global.h"
#include "commands/cd_cmd/cd.c"
#include "commands/exit_cmd/exit_cmd.c"
#include "DirName.c"
#include "functions/printScript.c"
#include "functions/useful_functions.c"
#include "functions/remove.c"
#include "functions/history.c"
#include "functions/reset.c"
#include "functions/remove_history_file.c"

#define error(a)   \
    {              \
        perror(a); \
        exit(1);   \
    };
#define MAXLINE 200
#define MAXARGS 20

/////////// reading commands:

int read_args(int *argcp, char *args[], int max, int *eofp)
{
    static char cmd[MAXLINE];
    char *cmdp;
    int ret, i;

    *argcp = 0;
    *eofp = 0;
    i = 0;
    while ((ret = read(0, cmd + i, 1)) == 1)
    {
        if (cmd[i] == '\n')
            break; // correct line
        i++;
        if (i >= MAXLINE)
        {
            ret = -2; // line too long
            break;
        }
    }
    switch (ret)
    {
    case 1:
        cmd[i + 1] = '\0'; // correct reading
        break;
    case 0:
        *eofp = 1; // end of file
        return 0;
        break;
    case -1:
        *argcp = -1; // reading failure
        fprintf(stderr, "Reading failure \n");
        return 0;
        break;
    case -2:
        *argcp = -1; // line too long
        fprintf(stderr, "Line too long -- removed command\n");
        return 0;
        break;
    }
    // Analyzing the line
    cmdp = cmd;
    for (i = 0; i < max; i++)
    { /* to show every argument */
        if ((args[i] = strtok(cmdp, " \t\n")) == (char *)NULL)
            break;
        cmdp = NULL;
    }
    if (i >= max)
    {
        fprintf(stderr, "Too many arguments -- removed command\n");
        return 0;
    }
    *argcp = i;
    return 1;
}

///////////////////////////////////////

void execute(int argc, char *argv[])
{
    int status;
    int pid = fork();

    switch (pid)
    {
    case -1:
        // Error on creating the child process.
        write(1, "Failed to Fork()\n", strlen("Failed to Fork()\n"));
        exit(23);
        // return 1;

    case 0:
        // Child process' program.
        // Execute the give command, if possible.
        if (execvp(argv[0], argv) < 0)
        {
            write(1, "Error while executing the command\n", strlen("Error while executing the command\n"));
            exit(23);
        }
    default:
        // Parent process execution.
        // Wait until child process terminates.
        wait(&status);
        // write(1,"wait ...\n",strlen("wait ...\n"));
    }
}

void pipe_(int argc, char **argv)
{
    int i;

    for (i = 1; i < argc - 1; i++)
    {
        int pd[2];
        pipe(pd);

        if (!fork())
        {
            dup2(pd[1], 1); // remap output back to parent
            if (execlp(argv[i], argv[i], NULL) < 0)
            {
                printf("taoussi layn3l tabounmouk\n");
                exit(23);
            }
            // execvp(argv[0], argv);
            perror("exec");
            abort();
        }

        // remap output from previous child to input
        dup2(pd[0], 0);
        close(pd[1]);
    }

    if (execlp(argv[i], argv[i], NULL) < 0)
    {
        printf("taoussi layn3l tabounmouk\n");
        exit(23);
    }
    // execvp(argv[0], argv);
    perror("exec");
    abort();
}

int main()
{

    int eof = 0;
    int argc;
    char *args[MAXARGS];
    char *cmd_list[9] = {"pwd", "cp", "ls", "cat", "exit", "mv", "Jarvis", "grep", "man"};
    int cmd_num;

    char current_directory[256];
    // system("rm -r Egypt");
    // system("cp -r EgyptLog/Egypt .");

    if (!reset())
    {
        char *msg = "Sorry, there has been a problem loading the game :(";
        printf("%s", msg);
        exit(1);
    }

    getcwd(current_directory, sizeof(current_directory));

    char home_dir[255];
    char jarvis_path[255];
    char menu_path[255];
    char introduction_path[255];

    getcwd(home_dir, sizeof(home_dir));
    strcpy(jarvis_path, home_dir);
    strcpy(menu_path, home_dir);
    strcpy(introduction_path, home_dir);

    strcat(home_dir, "/bin/");

    strcat(jarvis_path, "/.Jarvis/Help");
    strcat(menu_path, "/.History/Menu.txt");
    strcat(introduction_path, "/.History/Introduction");

    char *Prompt = current_directory;

    char *egypte_path = current_directory;
    strcat(egypte_path, "/Egypt");

    chdir(egypte_path);

    printScript(menu_path);

    // Wait until the user presses enter
    getchar();
    printScript(introduction_path);

    remove_history_file();

    while (1)
    {
        getcwd(current_directory, sizeof(current_directory));
        Prompt = (char *)malloc(strlen(current_directory));
        strcpy(Prompt, current_directory);
        strcat(Prompt, " $ ");

        printDirName();
        // write(0, Prompt, strlen(Prompt));
        cmd_num = -1;
        if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
        {
            /*if(!strcmp(args[2], "|"))
            {

                pipe_(argc,args);
            }*/

            cmd_num = check_cmd(args[0], cmd_list);

            char *his_path = "/home/k1/github_scaperoom/ScapeRoom/history_log.txt";
            int hist_fd = open(his_path, O_WRONLY | O_APPEND | O_CREAT, 0666);
            char *temp_cmd_path;
            if (!strcmp(args[0], "cd"))
            {

                if (argc == 2)
                {

                    if (strcmp(basename(current_directory), "Egypt") == 0 && strcmp(args[1], "..") == 0)
                        write(1, "You can't go back\n", strlen("You can't go back\n"));
                    else
                    {
                        if (!isDenied(basename(current_directory), args[1]))
                        {
                            cd(args[1]);
                            temp_cmd_path = (char *)malloc(strlen(args[1]) + strlen("cd \n"));
                            strcat(temp_cmd_path, "cd ");
                            strcat(temp_cmd_path, args[1]);
                            strcat(temp_cmd_path, "\n");
                            write(hist_fd, temp_cmd_path, strlen(temp_cmd_path));
                        }
                        else
                        {
                            char *msg = "Oh oh, looks like you cant get in. You need to find another way ! \n";
                            write(0, msg, strlen(msg));
                        }

                        // fputs("cd",his_file);
                    }

                    /*if (strcmp(args[1], "firstRoom") == 0)
                    {
                        if (isinInventeroy("key"))
                        {
                            cd(args[1]);
                            // history(argc, args);
                        }

                        else
                            write(1, "You don't have the necessary object to enter this room\n", strlen("You don't have the necessary object to enter this room\n"));
                    }*/
                }
                else
                {
                    write(1, "Error : cd should have one argument\n", 37);
                }
            }
            else if (!strcmp(args[0], "exit"))
            {
                if (argc == 1)
                {
                    if (exit_cmd())
                    {
                        if (!removeMain())
                        {
                            if (free_inventory() == 0)
                            {
                                exit(127);
                            }
                        }
                    }
                }
                else
                {
                    char *error = "Error : exit doesn t have argument\n";
                    write(1, error, strlen(error));
                }
            }
            else if (!strcmp(args[0], "history"))
            {
                printScript(OIER_HISTORY);
            }

            else if (strcmp(args[0], cmd_list[6]) == 0)
            {
                printScript(jarvis_path);
                write(hist_fd, "Jarvis", strlen("Jarvis"));
            }

            else if (cmd_num != -1)
            {
                args[0] = (char *)malloc(strlen(home_dir) + strlen(cmd_list[cmd_num]) + strlen("/bin/"));

                strcpy(args[0], home_dir);
                strcat(args[0], cmd_list[cmd_num]);
                execute(argc, args);

                history(argc, args);
            }
            else if (cmd_num == -1)
                write(1, "Command Not Found\n ", 18);
        }
    }
    if (eof)
        exit(0);
}
