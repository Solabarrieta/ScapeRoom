#include <unistd.h>
#include <stdio.h>

int history()
{
    char buff[20];
    read(STDIN_FILENO, buff, sizeof(buff));
    write(1, buff, sizeof(buff));
    return 0;
}