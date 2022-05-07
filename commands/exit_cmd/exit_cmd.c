#include <stdio.h>

int exit_cmd()
{
    char answer;
    char *msg = "Do you really want to exit the game?[y/n]: ";

    do
    {
        write(1, msg, strlen(msg));
        scanf(" %c", &answer);
        if (answer == 'y')
        {
            return 1;
        }
        else if (answer == 'n')
        {
            return 0;
        }
    } while (answer != 'y' && answer != 'n');
}
