#include <stdio.h>

int exit_cmd()
{
    char answer;

    do
    {
        printf("Do you really want to exit the game?[y/n]: ");
        scanf(" %c", &answer);
        if (answer == 'y')
        {
            return 1;
        }
        else if(answer == 'n')
        {
            return 0;
        }
    } while (answer != 'y' && answer != 'n');
}
