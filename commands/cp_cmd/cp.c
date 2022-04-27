#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

void cp(char *origin_file, char *dest_file)
{

    char buffer[1024];
    int files[2];
    ssize_t count;

    files[0] = open(origin_file, O_RDONLY);
    if (files[0] == -1)
    {
        write(1,"Error while opening the file\n",strlen("Error while opening the file\n"));
        close(files[0]);
        exit(23);
    }
    files[1] = open(dest_file, O_RDWR | O_CREAT, 0777);
    if (files[1] == -1)
    {
        write(1,"Error while opening the file\n",strlen("Error while opening the file\n"));
        close(files[1]);
        exit(23);
    }

    while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
        write(files[1], buffer, count);

}
int main(int argc, char **argv)
{
    if (argc==3)
    {

        cp(argv[1],argv[2]);
        return 1;
    }
    else
    {
        write(1,"error in the number of arguments\n",strlen("error in the number of arguments\n"));
        return 0;
    }

}





