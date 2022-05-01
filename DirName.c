/*#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char cur_dir[256];
    char *Prompt = cur_dir;
    getcwd(cur_dir, sizeof(cur_dir));
    Prompt = (char *)malloc(strlen(cur_dir));
    strcpy(Prompt, cur_dir);
    strcat(Prompt, "$");
    write(0, Prompt, strlen(Prompt));
}*/

/*#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int main()
{

    long path_max;
    path_max = pathconf(".", _PC_PATH_MAX);
    char cwd[path_max];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }
    return 0;
}*/
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
