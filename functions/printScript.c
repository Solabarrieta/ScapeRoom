#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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
        printf("path[%s]\n", path);
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

/*int main(int argc, char *argv[])
{
    printScript(argv[1]);
    char filename[] = "../.Jarvis/Help";
    char *path = realpath(filename, NULL);
    if (path == NULL)
    {
        printf("cannot find file with name[%s]\n", filename);
    }
    else
    {
        printf("path[%s]\n", path);
        free(path);
    }
}*/