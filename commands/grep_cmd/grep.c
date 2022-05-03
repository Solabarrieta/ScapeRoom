#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
//#include <conio.h>
/*
Black \033[0;30m
Red \033[0;31m
Green \033[0;32m
Yellow \033[0;33m
Blue \033[0;34m
Purple \033[0;35m
Cyan \033[0;36m
White \033[0;37m
Reset \033[0;0m
*/
void grep(char *word, char *filename)
{
    FILE *fp= fopen(filename, "r");
    char *line;
    //char delim[]=" ";
    char *printed_word[1024];
    int count=0,bytes_sum=0;
    int fd= open(filename, O_RDONLY);
    line=(char*)malloc(1024);


    if(fp != NULL)
    {
        while(fgets(line,1024,fp)!=NULL)
        {


            //bytes_sum+=sizeof(line);
            if(strstr(line,word)!=NULL)
            {

                //to split the line into words
                char *ptr=strtok(line," ");

                while(ptr!=NULL)
                {
                    if(strcmp(word,ptr)==0)
                    {
                        printf("\033[0;31m");
                        printf("%s ",ptr);
                        printf("\033[0;0m");
                    }
                    else
                        printf("%s ",ptr);
                    ptr=strtok(NULL," ");

                }
                count++;
            }

        }
    }
    else if(errno==ENOENT)
        write(1,"File does not exist\n",strlen("File does not exist\n"));
if(fp != NULL)
    fclose(fp);

}

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        grep(argv[1], argv[2]);
        return 1;
    }
    /*else if(argc == 4)
    {

    }*/
    else
    {
        write(1, "error in the number of arguments\n", strlen("error in the number of arguments\n"));
        return 0;
    }
}
