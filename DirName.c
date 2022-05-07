#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>

int printDirName()
{
    DIR *dir;
    struct dirent *ent;
    long path_max;
    path_max = pathconf(".", _PC_PATH_MAX);
    char dir_name[path_max];
    char current_dir[256];
    char parent[200];

    getcwd(current_dir, sizeof(current_dir));
    strcpy(current_dir, basename(current_dir));
    strcat(current_dir, " $  ");
    write(1, current_dir, strlen(current_dir));
}
