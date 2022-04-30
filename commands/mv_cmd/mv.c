#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return -1;
    }
    else
    {

        char buffer[1024];
        int fd_origin, fd_dest, chunk;
        struct stat permissions;

        stat(argv[1], &permissions);
        fd_origin = open(argv[1], O_RDONLY);
        fd_dest = open(argv[2], O_RDWR | O_CREAT, permissions.st_mode);

        do
        {
            chunk = read(fd_origin, buffer, sizeof(buffer));
            write(fd_dest, buffer, chunk);
        } while (chunk != 0);

        close(fd_origin);
        unlink(argv[1]);
        close(fd_dest);

        return 0;
    }
}
