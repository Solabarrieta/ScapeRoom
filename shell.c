// myShell0
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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

int execute(int argc, char *argv[])
{
    int status;
    int pid = fork();

    switch (pid)
    {
    case -1:
        // Error on creating the child process.
        return 1;

    case 0:
        // Child process' program.
        // Execute the give command, if possible.
        execvp(argv[0], argv);
        break;

    default:
        // Parent process execution.
        // Wait until child process terminates.
        //wait(&status);
        return status;
    }
}

int check_cmd(char *cmd,char *cmd_list[3])
{
    int i;
    for(i=0;i<3;i++)
    {
        if(strcmp(cmd,cmd_list[i])==0)
            return i;
    }
    return -1;

}

int main()
{

    int eof = 0;
    int argc;
    char *args[MAXARGS];
    char *cmd_list[3]={"pwd","cd","cp"};
    int cmd_num;

    char current_directory[256];
    getcwd(current_directory,sizeof(current_directory));

    //char *Prompt = "ScapeRoom -> ";
    char *Prompt = current_directory;
   // sc

    //create path to the game directory
    char *egypte_path=current_directory;
    strcat(egypte_path,"/Egypt");

    chdir(egypte_path);
     strcat(egypte_path,"--->$ ");

    while (1)
    {
        //write(0, Prompt, strlen(Prompt));
        write(0, Prompt, strlen(egypte_path));

        // write(1,"dddddddddddddddd77d",20);
        if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
        {
            cmd_num=check_cmd(args[0],cmd_list);
            if(cmd_num!=-1)
            {
                //commands/pwd_cmd/pwd"
                strcpy(args[0],"../commands/");
                strcat(args[0],cmd_list[cmd_num]);
                strcat(args[0],"_cmd/");
                strcat(args[0],cmd_list[cmd_num]);
                execute(argc, args);
               // Prompt = current_directory;
            }

            /*if(!strcmp(args[0],"pwd"))
            {
                //write(1,"ddddddddddddddddd",20);
                strcpy(args[0],"commands/pwd_cmd/pwd");
                execute(argc, args);
            }*/
            else
                write(1,"Command Not Found\n ",20);

        }
        if (eof)
            exit(0);
    }
}
