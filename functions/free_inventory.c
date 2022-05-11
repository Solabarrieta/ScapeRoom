#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../.Global/global.h"

int free_inventory()
{
    DIR *dir;
    struct dirent *ent;

    char home_dir[255];
    getcwd(home_dir, sizeof(home_dir));

    // char *invPath = "/home/oier/Documentos/uni/año2/ios/proyecto/ScapeRoom/.inventory";
    char *invPath = "/home/k1/github_scaperoom/ScapeRoom/.inventory";

    //char *invPath = strcat(home_dir, "/.inventory");
    char *currPath;
    char size[256];
    getcwd(currPath, sizeof(size));
    // char *inventory = inv_path;

    if ((dir = opendir(invPath)) != NULL)
    {
        chdir(invPath);
        while ((ent = readdir(dir)) != NULL)
        {
            /*  char buffer[256], *pathHome;
              int fileD, count;

              fileD = open(ent->d_name, O_RDONLY);
              while ((count = read(fileD, buffer, sizeof(buffer))) != 0)
              {
                  strcat(pathHome, buffer);
              }
              printf("%s  %s", pathHome, inventory);
              /*strcat(inventory, ent->d_name);
              int result = link(pathHome, inventory);*/
            if (strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0)
            {
                unlink(ent->d_name);
            }
        }
        chdir(currPath);
        return 0;
    }
    else
    {
        return -1;
    }
}

/*int main(int argc, char *argv[])
{
    free_inventory();
}*/
