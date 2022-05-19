#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../../functions/useful_functions.c"
#include "../../.Global/global.h"

int mv(char *origin_file, char *destination)
{

    /* if (link(origin_file, destination) == 0 && unlink(origin_file) == 0)
         return 1;
     else
     {
         perror("ERROR : can't move \n");
         return 0;
     }*/
    link(origin_file, destination);
    unlink(origin_file);
    return 1;
}
int main(int argc, char **argv)
{
    char inv[256];
    strcpy(inv, BACKPACK);
    if (argc == 3)
        if (!strcmp(argv[2], "backpack"))
        {
            if (!strcmp(argv[1], "lighter"))
            {
                char *msg = "Congratulations! You picked a lighter, now you can burn the hell out of that door!\n";
                write(0, msg, strlen(msg));
                strcat(inv, "lighter");
                mv(argv[1], inv);
                strcpy(inv, BACKPACK);
                return 1;
            }
            if (!strcmp(argv[1], "statue"))
            {
                char *msg = "This statue does not look very useful \n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "vase"))
            {
                char *msg = "This vase is empty, nothing useful here... \n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "graves"))
            {
                char *msg = "There are some graves empty and others untouched. Nothing around...\n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "parchments"))
            {
                char *msg = "Nolan takes the scrolls and uses the smartwatch to translate the written words and see if he can guess the code. \n It is impossible for him since they are so old that many words cannot even be read.  \n It does not seems to be nothing interesting. \n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "Skeleton1"))
            {
                char *msg = "The skeleton is full of dust. It has a golden ring in a finger.  Maybe it is useful. \n";
                write(0, msg, strlen(msg));

                return 1;
            }
            if (!strcmp(argv[1], "Skeleton1/ring1"))
            {
                char *msg = "Nolan takes the skeleton's ring, it has two numbers. it can be part of the key. \n";
                write(0, msg, strlen(msg));
                strcat(inv, "ring1");
                mv(argv[1], inv);
                strcpy(inv, BACKPACK);
                return 1;
            }
            if (!strcmp(argv[1], "Skeleton2"))
            {
                char *msg = "The skeleton is full of dust. It has a golden ring in a finger.  Maybe it is useful.\n";
                write(0, msg, strlen(msg));

                return 1;
            }
            if (!strcmp(argv[1], "Skeleton2/ring2"))
            {
                char *inventory = "../.inventory/skeleton2/ring2";
                char *msg = "Nolan takes the skeleton's ring, it has two numbers. it can be part of the key. \n";
                write(0, msg, strlen(msg));
                strcat(inv, "ring2");
                mv(argv[1], inv);
                strcpy(inv, BACKPACK);
                return 1;
            }
            if (!strcmp(argv[1], "tombStones"))
            {
                char *msg = "There is a description of the deaths in each of them, with their name and death date. Nothing interesting,... \n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "library"))
            {
                char *msg = "Nolan begins to read and pick up books desperately without understanding anything. Suddenly, without meaning to,he hits a book with his head and the shelf moves...LEAVED ROOM FOR A NEW ROOM! The door to follow was the shelf itself. \n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "ObjectsOfValue"))
            {
                char *msg = "There are some objects that cuold pay a hole continent!! There is some valuable jewellery such as necklaces, earrings,...gold everywhere. But there's not our egg... \n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "weapons"))
            {
                char *msg = "Nolan takes the weapons but nothing, there is nothing written and they don't seem to be useful. \n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "gold coins"))
            {
                char *msg = "There is a gigant mount of gold coins from the ancient Egypt. Just coins. \n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "statues"))
            {
                char *msg = "Some statues of women and men, they seem to be pharaohns. Nothing interesting,... \n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "tomb"))
            {
                char *msg = "In the center of the room is the tomb of the pharaoh, closed. Nolan tries to open it but it's too hard, so he tries it with a crowbar from his inventory.POW !It opens.A bomb of dust and stink erupts from within.Once it clears up you can clearly see the pharaoh's mummy clutching the golden egg. \n";
                write(0, msg, strlen(msg));
                return 1;
            }
            if (!strcmp(argv[1], "Tomb/goldenEgg"))
            {
                char *msg = "Nolan, finally, takes the egg. The adventere has end! TinTinTin… Congratulations! You've won! \n";
                write(0, msg, strlen(msg));
                strcat(inv, "goldenEgg");
                mv(argv[1], inv);
                strcpy(inv, BACKPACK);
                char msg2[256];
                strcpy(msg2, "Nolan leaves the pyramid proud of his adventure. On his way back to his plane, he bumps into a rock \n and drops the egg off a cliff into a river.The egg ends up being lost forever and Nolan stops being a thief because of \n the shame that he feels. \n");
                write(0, msg2, strlen(msg2));
                sleep(5);

                return 1;
            }
            if (!strcmp(argv[1], "treasure"))
            {
                char *msg = "There are some treasures, chests full of gold, precious gems such as ruby-s, esmeralds,... The egg isn't here. \n";
                write(0, msg, strlen(msg));
                return 1;
            }
        }
        else
        {
            mv(argv[1], argv[2]);
        }
    /*{
        // if file 1  exist
        if (access(argv[1], F_OK) == 0)
        {

            printf("%s file exists \n ", argv[1]);
            // if it's a directory
            if (isDir(argv[2]) == 0)
            {
                if (opendir(argv[2]))
                {

                    printf("%s is a dir \n ", argv[2]);
                    char current_directory[256];
                    getcwd(current_directory, sizeof(current_directory));

                    strcat(current_directory, "/");
                    strcat(current_directory, argv[2]);
                    strcat(current_directory, "/");
                    strcat(current_directory, argv[1]);

                    mv(argv[1], current_directory);
                    return 1;
                }
                else
                {
                    rename(argv[1], argv[2]);
                    return 1;
                }
            }
            // if file exists
            else if (access(argv[2], F_OK) == 0)
            {
                unlink(argv[2]);
                rename(argv[1], argv[2]);
                return 1;
            }

            else
            {
                write(1, "error in the number of arguments\n", strlen("error in the number of arguments\n"));
                return 0;
            }
        }
        else
        {
            write(1, "file 1 doesn't exist\n", strlen("file 1 doesn't exist\n"));
            return 0;
        }
    }*/
}
