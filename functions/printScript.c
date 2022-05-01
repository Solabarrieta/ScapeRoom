#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void printScript(char *pathName)
{
    char buffer[124];
    int fd, fd2, size;
    fd = open(pathName, O_RDONLY);

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
}*/