#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../../.Global/global.c"

int mv(char *origin, char *dest)
{
    /*if (link(origin, dest) < 0)
    {
        perror("ERROR : can't create a link\n");
        return -1;
    }
    else
    {
        if(unlink)
        return unlink(origin);
    }*/
    link(origin, dest);
    unlink(origin);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return -1;
    }
    else
    {

        char buffer[1024];
        char *msg;
        // int fd_origin, fd_dest, chunk;
        // struct stat permissions;

        /*stat(argv[1], &permissions);
        fd_origin = open(argv[1], O_RDONLY);
        fd_dest = open(argv[2], O_RDWR | O_CREAT, permissions.st_mode);

        do
        {
            chunk = read(fd_origin, buffer, sizeof(buffer));
            write(fd_dest, buffer, chunk);
        } while (chunk != 0);*/

        if (!strcmp(argv[2], "inventory"))
        {
            char *path;
            if (!strcmp(argv[1], "lighter"))
            {
                msg = "Fuck yeah, you found a lighter, burn the hell out of that door!";
                write(1, msg, strlen(msg));
                path = inv_path;
                strcat(path, "lighter"); // strcat solo funciona con un puntero a un array declarado o con un array
                mv(argv[1], path);
            }
        }
        else
        {
            mv(argv[1], argv[2]);
        }

        return 0;
    }
}
