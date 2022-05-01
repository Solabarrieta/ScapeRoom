#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int touch(char *filename)
{

    // user has write and read permission
    // group has read permission.
    // others have read permission.
    int fd = open(filename, O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

    if (fd == -1)
    {
        write(1,"ERROR! while creating the file", strlen("ERROR! while creating the file"));
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        touch(argv[1]);
        return 1;
    }
    else
    {
        write(1,"touch should have one argument(file name)\n",strlen("touch should have one argument(file name)\n"));
        return 0;
    }

}
