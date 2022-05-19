#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../.Global/global.h"
#define MAXLINE 200
#define MAXARGS 20
// function to check if the given file is a real file or directory
// return 0 if it's a directory
// else is not dir
int isDir(char *filename)
{
    struct stat info;
    stat(filename, &info);
    return S_ISREG(info.st_mode);
}

// function to check if cmd exists in cmd_list
int check_cmd(char *cmd, char *cmd_list[11])
{
    // int size= sizeof(cmd_list[0])/sizeof(cmd_list[0][0]);
    int i;
    for (i = 0; i < 11; i++)
    {
        if (strcmp(cmd, cmd_list[i]) == 0)
            return i;
    }
    return -1;
}

// function to check if a file exists in Inventory
int isinInventeroy(char *filename)
{
    char *file_path;

    char home_dir[255];

    // getcwd(home_dir, sizeof(home_dir));
    // char *cut = strstr(home_dir, "/ScapeRoom");

    file_path = (char *)malloc(strlen(BACKPACK) + strlen(filename));

    // strncpy(file_path, home_dir, cut - home_dir);
    // strcat(file_path, "/ScapeRoom/.inventory/");*/
    strcpy(file_path, BACKPACK);
    strcat(file_path, filename);

    FILE *file;
    file = fopen(file_path, "r");

    if (file)
    {
        // printf("Object exists in Inventory\n");
        fclose(file);
        return 1;
    }
    else
    {
        // printf("You don't have the necessary object to enter this room\n");
        return 0;
    }
}
// function to get the root path of the game
char *getRootPath()
{
    char home_dir[255];
    char *root_path;

    getcwd(home_dir, sizeof(home_dir));
    char *cut = strstr(home_dir, "/ScapeRoom");

    root_path = (char *)malloc(strlen(home_dir) + strlen("/ScapeRoom/") - strlen(cut));

    strncpy(root_path, home_dir, cut - home_dir);

    strcat(root_path, "/ScapeRoom/");

    return root_path;
}

int isDirectoryEmpty(char *dirname)
{
    int n = 0;
    struct dirent *d;
    DIR *dir = opendir(dirname);
    if (dir == NULL) // Not a directory or doesn't exist
        return 1;
    while ((d = readdir(dir)) != NULL)
    {
        if (++n > 2)
            break;
    }
    closedir(dir);
    if (n <= 2) // Directory Empty
        return 1;
    else
        return 0;
}

int free_inventory()
{
    DIR *dir;
    struct dirent *ent;

    char home_dir[255];
    getcwd(home_dir, sizeof(home_dir));

    char invPath[256] = BACKPACK;
    // char *invPath = "/home/k1/github_scaperoom/ScapeRoom/.inventory";

    // char *invPath = strcat(home_dir, "/.inventory");
    char *currPath;
    char size[256];
    getcwd(currPath, sizeof(size));
    // char *inventory = inv_path;

    if ((dir = opendir(invPath)) != NULL)
    {
        chdir(invPath);
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0)
            {
                unlink(ent->d_name);
            }
        }
        chdir(currPath);
        if (isDirectoryEmpty(invPath))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return -1;
    }
}

int isDenied(char *dir, char *room)
{
    int result = 0;
    if (strcmp(dir, "Great_Pyramid") == 0 && strcmp(room, "FirstRoom") == 0)
    {
        result = 0;
    }
    else if (strcmp(dir, "FirstRoom") == 0 && strcmp(room, "SecondRoom") == 0)
    {
        if (isinInventeroy("lighter"))
        {
            result = 0;
        }
        else
        {
            result = 1;
        }
    }
    else if (strcmp(dir, "SecondRoom") == 0 && strcmp(room, "ThirdRoom") == 0)
    {
        if (isinInventeroy("ring1") && isinInventeroy("ring2"))
        {
            result = 0;
        }
        else
        {
            result = 1;
        }
    }
    else if (strcmp(dir, "ThirdRoom") == 0 && strcmp(room, "FinalRoom") == 0)
    {
        result = 0;
    }
    return result;
}

// Function to print the contento of a file
void printScript(char *relPath)
{
    char buffer[124];
    int fd, fd2, size;

    char *path = realpath(relPath, NULL);

    fd = open(path, O_RDONLY);

    if (path == NULL)
    {
        printf("cannot find file with name[%s]\n", relPath);
    }
    else
    {
        free(path);
    }

    /*while ((count = read(fd, buffer, sizeof(buffer))) != 0)
    {
        write(1, buffer, count);
    }*/
    write(1, "\n", strlen("\n"));
    do
    {
        size = read(fd, buffer, sizeof(buffer));
        write(1, buffer, size);
    } while (size != 0);
    write(1, "\n", strlen("\n"));
}

int reset()
{
    char auxPath[256];
    char path[256] = HOME;

    // Creating the main directories
    mkdir("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt", S_IRWXU);
    mkdir("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid", S_IRWXU);
    mkdir("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom", S_IRWXU);
    mkdir("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom", S_IRWXU);
    mkdir("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/Skeleton1", S_IRWXU);
    mkdir("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/Skeleton2", S_IRWXU);
    mkdir("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/ThirdRoom", S_IRWXU);
    mkdir("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/ThirdRoom/BookStore", S_IRWXU);
    mkdir("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/ThirdRoom/FinalRoom", S_IRWXU);
    mkdir("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/ThirdRoom/FinalRoom/Tomb", S_IRWXU);

    // Creating the files
    //  First Room
    strcat(path, "Great_Pyramid");
    strcpy(auxPath, path);
    strcat(path, "/brick1");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/brick2");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/brick3");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/brick4");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);

    strcat(path, "/FirstRoom");
    strcpy(auxPath, path);
    strcat(path, "/statue");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/vase");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/lighter");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);

    // Second Room
    strcat(path, "/SecondRoom");
    strcpy(auxPath, path);
    strcat(path, "/graves");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/parchments");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/parchments");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/tombStones");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/Skeleton1/ring1");
    int ring1 = open(path, O_RDWR | O_CREAT, 0700);
    write(ring1, "2 4", strlen("2 4"));
    strcpy(path, auxPath);
    strcat(path, "/Skeleton2/ring2");
    int ring2 = open(path, O_RDWR | O_CREAT, 0700);
    write(ring2, "7 1", strlen("7 1"));
    strcpy(path, auxPath);

    // Third Room
    strcat(path, "/ThirdRoom");
    strcpy(auxPath, path);
    strcat(path, "/BookStore/book1");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/BookStore/book2");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/BookStore/book3");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/ObjectsOfValue");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/weapons");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);

    // Final Room
    strcat(path, "/FinalRoom");
    strcpy(auxPath, path);
    strcat(path, "/goldCoins");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/statues");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/Tomb/goldenEgg");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/treasure");
    open(path, O_RDWR | O_CREAT, 0700);

    chmod("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/ThirdRoom/FinalRoom", 0600);
    chmod("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom", 0600);

    return 1;
}

int history(int args, char *argv[])
{
    char *buffer;
    char arg1[20] = "";
    char arg2[20] = "";
    char arg3[20] = "";

    // generate the bin folder path
    char *root_path;
    char home_dir[255];
    getcwd(home_dir, sizeof(home_dir));
    char *cut = strstr(home_dir, "/ScapeRoom");
    root_path = (char *)malloc(strlen(home_dir) + strlen("/ScapeRoom/bin/"));
    strncpy(root_path, home_dir, cut - home_dir);
    strcat(root_path, "/ScapeRoom/bin/");
    ////////////////////////////////////////////

    int fd = open(HISTORY, O_RDWR | O_CREAT, 0777);
    lseek(fd, 0, SEEK_END);
    // printf("%s", argv[0]);

    if (args == 3)
    {
        buffer = (char *)malloc(strlen(argv[0]) + strlen(argv[1]) + strlen(argv[2]) + strlen("  \n"));
        strcpy(arg1, argv[0]);
        strcpy(arg2, argv[1]);
        strcpy(arg3, argv[2]);
        strcat(buffer, arg1);
        strcat(buffer, " ");
        strcat(buffer, arg2);
        strcat(buffer, " ");
        strcat(buffer, arg3);
        strcat(buffer, "\n");
        // printf("%s", buffer);
    }
    else if (args == 2)
    {
        buffer = (char *)malloc(strlen(argv[0]) + strlen(argv[1]) + strlen("  \n"));
        strcpy(arg1, argv[0]);
        strcpy(arg2, argv[1]);
        strcat(buffer, arg1);
        strcat(buffer, " ");
        strcat(buffer, arg2);
        strcat(buffer, "\n");
        // printf("%s", buffer);
    }
    else if (args == 1)
    {
        buffer = (char *)malloc(strlen(argv[0]) + strlen("  \n"));
        strcpy(arg1, argv[0]);
        strcat(buffer, arg1);
        strcat(buffer, "\n");
        // printf("%s", buffer);
    }

    buffer = buffer + strlen(root_path);

    write(fd, buffer, strlen(buffer));
    close(fd);
    return 0;
}

void remove_history_file()
{

    if (access("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/history_log.txt", F_OK) == 0)
    {
        // file exists
        char *argv[20] = {
            "rm",
            "-r",
            "/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/history_log.txt"};
        int status;
        int pid = fork();
        if (pid == 0)
        {
            execvp("rm", argv);
        }

        while (wait(&status) != -1 || errno != ECHILD)
            ;
    }

    if (access("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/history_log.txt", F_OK) != 0)
    {
        // file doesn't exist
        int fd = open("/users/alumnos/acaf/acaf0240/Proyecto/ScapeRoom/history_log.txt", O_RDWR | O_CREAT, 0777);
    }
}

int removeMain()
{

    char *argv[20] = {
        "rm",
        "-r",
        HOME};
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

// function to check if there is a pipe in str
//no pipes => return 0 else 1
int isPipe(char* str, char *argspipe[])
{
    int i;
    for (i = 0; i < 2; i++) {
        argspipe[i] = strsep(&str, "|");
        if (argspipe[i] == NULL)
            break;
    }

    if (argspipe[1] == NULL)
        return 0;
    else {
        return 1;
    }
}

// function to split command by space
// "ls test" => "ls" "test"
void splitCmd(char* str, char *args[])
{
    int i;

    for (i = 0; i < MAXLINE; i++) {
        args[i] = strsep(&str, " ");

        if (args[i] == NULL)
            break;
        if (strlen(args[i]) == 0)
            i--;
    }
}

//function to find the command before and after the pipe
//input = man cat | wc ==>
//args = man cat
//argspipe = wc
//return 1 if it's one command or 2 if there is a pipe
int processString(char *input[], char *args[], char *argspipe[])
{

    char *str="";
    str = (char *)malloc(strlen(*input));
    int n=0;
    for(int i=0;i<MAXARGS;i++)
    {

        if(input[i]==NULL)
            break;
        else
            n++;

    }

    for(int i=0;i<n;i++)
    {

        strcat(str,input[i]);
        strcat(str," ");
    }

    char* strpiped[2];
    int piped = 0;

    piped = isPipe(str, strpiped);

    if (piped) {
        splitCmd(strpiped[0], args);
        splitCmd(strpiped[1], argspipe);

    } else {

        splitCmd(str, args);
    }
    return 1 + piped;
}





























