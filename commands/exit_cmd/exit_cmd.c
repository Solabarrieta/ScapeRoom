#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int exit_cmd()
{
    char response;

    do
    {
        printf("Do you really want to exit the game?");
        scanf("%c", &response);
    } while (response != 'y' || response != 'n');

    if (response == 'y')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}