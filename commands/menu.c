/**
 * @file menu.c
 * @author Ainara Escribano, Ane Amengual
 * @brief Menu file, for the scaperoom.
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <string.h>

/**
 * @brief The menu screen!
 */
void print_menu()
{
    println("                              *                                  ");
    println("                          *********                              ");
    println("                      ******************                         ");
    println("                ******************************                   ");
    println("         ******@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*******           ");
    println("  ***********|********** SCAPEROOM ***********|************      ");
    println("**************|                                |***************  ");
    println("**************|***** \"Hangover in Egypt\" ****|***************  ");
    println("**************|                                |***************  ");
    println("**************|  \"Quick! You have to scape!\" |***************  ");
    println("**************|                                |***************  ");
    println("**************|*** Press enter key to begin ***|***************  ");
    println("***************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****************  ");
    println("***************************************************************  ");
    println("***************************************************************  ");
    println("***************************************************************  ");
}

int main(int argc, char *argv[])
{
    print_menu();
}