#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include "../../.Global/global.h"

void cat(char *filename)
{
    // file descriptor : open file in read mode
    int fd = open(filename, O_RDONLY);
    char buffer[256];
    // size_t is the size of an alloctaed block in memory
    int count;

    if (fd != -1)
    {
        write(1, "\n", strlen("\n"));
        while ((count = read(fd, buffer, sizeof(buffer))) != 0)
            write(1, buffer, count);
        write(1, "\n", strlen("\n"));
    }
    else if (errno == ENOENT)
        write(1, "File does not exist\n", strlen("File does not exist\n"));
    /*else if(errno!=ENOTDIR)
    {
        write(1,filename,strlen(filename));
        write(1,": is not a file\n",strlen(": is not a file\n"));
    }*/

    close(fd);
}
int main(int argc, char *argv[])
{
    char inv[256] = BACKPACK;
    if (argc == 2)
    {
        if (!strcmp(argv[1], "ring1"))
        {
            strcat(inv, "ring1");
            strcpy(argv[1], inv);
        }
        else if (!strcmp(argv[1], "ring2"))
        {
            strcat(inv, "ring2");
            strcpy(argv[1], inv);
        }
        cat(argv[1]);
    }
    else
    {
        write(1, "error cat should have one arguments\n", strlen("error cat should have one arguments\n"));
        return 1;
    }

    return 0;
}
