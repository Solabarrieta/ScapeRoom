#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
* @brief This void method will call to the open function. In case of error, the open system call will return -1 and an error message will appear.
*
* @param f_name that will be the wanted file name to be created.
* @return int 1 iff failure.
*/
int touch(char *f_name)
{
    char *err_title = THE_SYSTEM;

    // S_IWUSR: 00400 user has write permission
    // S_IRUSR: 00400 user has read permission.
    // S_IRGRP: 00040 group has read permission.
    // S_IROTH: 00004 others have read permission.
    int fd = open(f_name, O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

    if (fd == -1)
    {
        printerr("Oh no! I cannot create the object!", err_title);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    char *err_title = THE_SYSTEM;

    if (argc != 2) {
        printerr("Oh no, you hit your hand while you where obtaining the object.", err_title);
        return 1;
    }

    return touch(argv[1]);
}
#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
* @brief This void method will call to the open function. In case of error, the open system call will return -1 and an error message will appear.
*
* @param f_name that will be the wanted file name to be created.
* @return int 1 iff failure.
*/
int touch(char *f_name)
{
    char *err_title = THE_SYSTEM;

    // S_IWUSR: 00400 user has write permission
    // S_IRUSR: 00400 user has read permission.
    // S_IRGRP: 00040 group has read permission.
    // S_IROTH: 00004 others have read permission.
    int fd = open(f_name, O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

    if (fd == -1)
    {
        printerr("Oh no! I cannot create the object!", err_title);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    char *err_title = THE_SYSTEM;

    if (argc != 2) {
        printerr("Oh no, you hit your hand while you where obtaining the object.", err_title);
        return 1;
    }

    return touch(argv[1]);
}
