// myShell0
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include ".Global/global.h"
#include "commands/cd_cmd/cd.c"
#include "commands/exit_cmd/exit_cmd.c"
#include "DirName.c"
#include "functions/useful_functions.c"

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
// execute commands without pipes
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

// execute commands with pipes
void executePipe(char *args[], char *argspipe[])
{

    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("Pipe failed");
        exit(1);
    }

    if (fork() == 0)
    {
        close(STDOUT_FILENO);
        // replacing stdout with pipe write
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);

        execvp(args[0], args);
        perror("execvp of cmd 1 failed");
        exit(1);
    }

    if (fork() == 0)
    {
        close(STDIN_FILENO);
        // replacing stdin with pipe read
        dup(fd[0]);
        close(fd[1]);
        close(fd[0]);

        /* char* cmd[] = { "wc", "-l", 0};
         char* cmd[] = { "/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/bin/wc", "-l", 0};
        execvp(cmd[0], cmd);*/

        execvp(argspipe[0], argspipe);
        perror("OOOPS !! Error executing the second command");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(0);
    wait(0);
}

int main()
{

    char *firstCmd[MAXLINE];
    char *secondCmd[MAXLINE];
    int withPipe = 0;

    int eof = 0;
    int argc;
    char *args[MAXARGS];
    char *cmd_list[11] = {"pwd", "cp", "ls", "cat", "exit", "mv", "Jarvis", "grep", "man", "push", "wc"};
    int cmd_num;
    int firstRoom, finalRoom = 0;

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
    int countGP, countFR, countSR, countTR, countLR = 0;

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
    getchar();
    char intro2[256] = SCRIPT;
    strcat(intro2, "Introduction2");
    printScript(intro2);
    getchar();
    char intro3[256] = SCRIPT;
    strcat(intro3, "Introduction3");
    printScript(intro3);
    getchar();
    char help[256] = SCRIPT;
    strcat(help, "Help.txt");
    printScript(help);
    getchar();

    remove_history_file();

    while (1)
    {
        /*getcwd(current_directory, sizeof(current_directory));
        Prompt = (char *)malloc(strlen(current_directory));
        strcpy(Prompt, current_directory);
        strcat(Prompt, " $ ");*/

        if (!strcmp(basename(current_directory), "Great_Pyramid"))
        {
            if (countGP++ < 1)
            {
                char script[256] = SCRIPT;
                strcat(script, "Great_Pyramid");
                printScript(script);
            }
        }

        printDirName();
        // write(0, Prompt, strlen(Prompt));
        cmd_num = -1;
        if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
        {
            withPipe = processString(args, firstCmd, secondCmd);

            cmd_num = check_cmd(args[0], cmd_list);

            char *his_path = "/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/history_log.txt";
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
                        if (!isDenied(basename(current_directory), args[1], firstRoom, finalRoom))
                        {
                            cd(args[1]);
                            temp_cmd_path = (char *)malloc(strlen(args[1]) + strlen("cd \n"));
                            strcat(temp_cmd_path, "cd ");
                            strcat(temp_cmd_path, args[1]);
                            strcat(temp_cmd_path, "\n");
                            write(hist_fd, temp_cmd_path, strlen(temp_cmd_path));
                            close(hist_fd);
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
                printScript(HISTORY);
            }

            else if (strcmp(args[0], cmd_list[6]) == 0)
            {
                char path[256] = JARVIS;

                /*if (strcmp(args[1], "help") == 0)
                {
                    strcat(path, "Help");
                }*/

                strcat(path, basename(current_directory));
                printScript(path);
                write(hist_fd, "Jarvis", strlen("Jarvis"));
                close(hist_fd);
                strcpy(path, JARVIS);
            }
            else if (strcmp(args[0], "push") == 0)
            {
                char path[256];
                strcpy(path, current_directory);
                if (strcmp(args[1], "brick3") == 0)
                {
                    firstRoom = 1;
                }
                else if (!strcmp(args[1], "BookStore/book3"))
                {
                    finalRoom = 1;
                }
            }

            else if (cmd_num != -1)
            {
                args[0] = (char *)malloc(strlen(home_dir) + strlen(cmd_list[cmd_num]));

                strcpy(args[0], home_dir);
                strcat(args[0], cmd_list[cmd_num]);

                char *tmp;
                /* if(secondCmd[0]!=NULL){
                 tmp=malloc(strlen(secondCmd[0]));
                 strcpy(tmp,secondCmd[0]);

                 secondCmd[0] = (char *)malloc(strlen(home_dir) + strlen(tmp) + strlen("/bin/"));
                 strcpy(secondCmd[0], home_dir);
                 strcat(secondCmd[0], tmp);
                 }*/
                // char *tmp;
                if (firstCmd[0] != NULL)
                {
                    tmp = malloc(strlen(firstCmd[0]));
                    strcpy(tmp, firstCmd[0]);

<<<<<<< HEAD
                    firstCmd[0] = (char *)malloc(strlen(home_dir) + strlen(tmp) + strlen("/bin/"));
                    strcpy(firstCmd[0], home_dir);
                    strcat(firstCmd[0], tmp);
=======
                firstCmd[0] = (char *)malloc(strlen(home_dir) + strlen(tmp) );
                strcpy(firstCmd[0], home_dir);
                strcat(firstCmd[0], tmp);
>>>>>>> e1e02e6b82878985fea814d5f04e1eeee7f9eaaa
                }

                if (withPipe == 1)
                {
                    execute(argc, args);
                    free(args[0]);
                }


                history(argc, args);

                if (withPipe == 2)
                {
<<<<<<< HEAD
                    if (strcmp(secondCmd[0], "wc") == 0)
=======
                    if(strcmp(secondCmd[0],"wc")==0)
                    {
>>>>>>> e1e02e6b82878985fea814d5f04e1eeee7f9eaaa
                        executePipe(firstCmd, secondCmd);
                        free(firstCmd[0]);
                    }

                    else
                        write(1, "NO pipe available here use wc\n", strlen("NO pipe available here use wc\n"));
                }
            }
            else if (cmd_num == -1)
                write(1, "Command Not Found\n ", 18);
        }

        if (isinInventeroy("goldenEgg"))
        {
            char msg[256];
            char home[256];
            strcpy(home, HOME);
            if (cd(home) == -1)
            {
                write(3, strerror(errno), strlen(strerror(errno)));
            }
            else
            {
                strcpy(msg, "Congratulations, you finished the game! We hope you enjoyed! \n");
                write(0, msg, strlen(msg));

                if (!removeMain())
                {
                    if (free_inventory() == 0)
                    {
                        exit(127);
                    }
                }
            }
        }
    }
    if (eof)
        exit(0);
}
