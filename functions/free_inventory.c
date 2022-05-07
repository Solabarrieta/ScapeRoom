#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int free_inventory()
{
    DIR *dir;
    struct dirent *ent;
    char *invPath = "/home/oier/Documentos/uni/año2/ios/proyecto/ScapeRoom/.inventory";
    char *currPath;
    char size[256];
    getcwd(currPath, sizeof(size));
    // write(1, currPath, strlen(currPath));

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
        return 0;
    }
    else
    {
        return -1;
    }
}