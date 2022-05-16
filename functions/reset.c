#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../.Global/global.h"
#include <string.h>
#include <fcntl.h>

int reset()
{
    char auxPath[256];
    char path[256] = OIER_HOME;

    // Creating the main directories
    mkdir("/home/oier/Documentos/uni/año2/ios/proyecto/ScapeRoom/Egypt", S_IRWXU);
    mkdir("/home/oier/Documentos/uni/año2/ios/proyecto/ScapeRoom/Egypt/Great_Pyramid", S_IRWXU);
    mkdir("/home/oier/Documentos/uni/año2/ios/proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom", S_IRWXU);
    mkdir("/home/oier/Documentos/uni/año2/ios/proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom", S_IRWXU);
    mkdir("/home/oier/Documentos/uni/año2/ios/proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/ThirdRoom", S_IRWXU);
    mkdir("/home/oier/Documentos/uni/año2/ios/proyecto/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/ThirdRoom/FinalRoom", S_IRWXU);

    /*mkdir("/home/k1/github_scaperoom/ScapeRoom/Egypt", S_IRWXU);
    mkdir("/home/k1/github_scaperoom/ScapeRoom/Egypt/Great_Pyramid", S_IRWXU);
    mkdir("/home/k1/github_scaperoom/ScapeRoom/Egypt/Great_Pyramid/FirstRoom", S_IRWXU);
    mkdir("/home/k1/github_scaperoom/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom", S_IRWXU);
    mkdir("/home/k1/github_scaperoom/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/ThirdRoom", S_IRWXU);
    mkdir("/home/k1/github_scaperoom/ScapeRoom/Egypt/Great_Pyramid/FirstRoom/SecondRoom/ThirdRoom/FinalRoom", S_IRWXU);*/

    // Creating the files
    //  First Room
    strcat(path, "Great_Pyramid");
    strcat(path, "/FirstRoom");
    strcpy(auxPath, path);
    strcat(path, "/statue");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/vase");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);

    // Second Room
    strcat(path, "/SecondRoom");
    strcpy(auxPath, path);
    strcat(path, "/graves");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/parchments");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/parchments");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/skeleton1");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/skeleton2");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/tombStones");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);

    // Third Room
    strcat(path, "/ThirdRoom");
    strcpy(auxPath, path);
    strcat(path, "/library");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/ObjectsOfValue");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/weapons");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);

    // Final Room
    strcat(path, "/FinalRoom");
    strcpy(auxPath, path);
    strcat(path, "/goldCoins");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/statues");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/tomb");
    open(path, O_RDWR | O_CREAT, 0700);
    strcpy(path, auxPath);
    strcat(path, "/treasure");
    open(path, O_RDWR | O_CREAT, 0700);

    return 1;
}
