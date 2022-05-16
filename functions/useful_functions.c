#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

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

// function to check if a file exists in Inventory
int isinInventeroy(char *filename)
{
    char *file_path;

    char home_dir[255];

    getcwd(home_dir, sizeof(home_dir));
    char *cut = strstr(home_dir, "/ScapeRoom");

    file_path = (char *)malloc(strlen(home_dir) + strlen("/.inventory/") + strlen(filename));

    strncpy(file_path, home_dir, cut - home_dir);
    strcat(file_path, "/ScapeRoom/.inventory/");
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

    char *invPath = "/home/oier/Documentos/uni/año2/ios/proyecto/ScapeRoom/.inventory";
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
