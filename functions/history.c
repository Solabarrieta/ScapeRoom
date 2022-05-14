#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int history(int args, char *argv[])
{
    char buffer[256];
    char arg1[20] = "";
    char arg2[20] = "";
    char arg3[20] = "";
    int fd = open("../history_log.txt", O_RDWR | O_CREAT, 0777);
    lseek(fd, 0, SEEK_END);
    printf("%s", argv[0]);

    if (args == 3)
    {
        strcpy(arg1, argv[0]);
        strcpy(arg2, argv[1]);
        strcpy(arg3, argv[2]);
        strcat(buffer, arg1);
        strcat(buffer, " ");
        strcat(buffer, arg2);
        strcat(buffer, " ");
        strcat(buffer, arg3);
        strcat(buffer, "\n");
        printf("%s", buffer);
    }
    else if (args == 2)
    {

        strcpy(arg1, argv[0]);
        strcpy(arg2, argv[1]);
        strcat(buffer, arg1);
        strcat(buffer, " ");
        strcat(buffer, arg2);
        strcat(buffer, "\n");
        printf("%s", buffer);
    }
    else if (args == 1)
    {
        strcpy(arg1, argv[0]);
        strcat(buffer, arg1);
        strcat(buffer, "\n");
        printf("%s", buffer);
    }
    // read(STDIN_FILENO, buff, sizeof(buff));

    write(fd, buffer, strlen(buffer));
    close(fd);
    return 0;
}

/*int main(int argc, char *argv[])
{
    history(argc, argv);
}*/
