/**
 * @file cp.c
 * @author Ainara Escribano, Ane Amengual
 * @brief cp command to copy files
 * @version 0.2
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *buffer[1024];
    char *err_title = THE_SYSTEM;
    char *err;
    int origin, end, oread, owrite;

    if (argc != 3)
    {
        printerr("Revise your notes. Usage: cp file new_file.", err_title);
        return 1;
    }

    origin = open(argv[1], O_RDONLY);

    if (origin < 0)
    {
        printerr("Error opening the file.", err_title);
        exit(EXIT_FAILURE);
    }

    end = open(argv[2], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

    if (end < 0)
    {
        err = (char *)malloc(strlen("Error opening file %s errno = %d") + strlen(argv[2]) + sizeof(errno));
        sprintf(err, "Error opening file %s errno = %d", argv[2], errno);
        printerr(err, err_title);
        _exit(EXIT_FAILURE);
    }

    oread = read(origin, buffer, sizeof(buffer));

    while (oread > 0)
    {
        if (write(end, buffer, oread) != oread)
        {
            err = (char *)malloc(strlen("Error in writing data to %s") + strlen(argv[2]));
            sprintf(err, "Error in writing data to %s", argv[2]);
            printerr(err, err_title);
            _exit(EXIT_FAILURE);
        }

        oread = read(origin, buffer, sizeof(buffer));
    }

    return 0;
}
