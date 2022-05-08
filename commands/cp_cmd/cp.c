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
    int state;
    ssize_t count;
    struct stat info;

    files[0] = open(origin_file, O_RDONLY);
    // get rhe permissions of the origin file
    stat(origin_file, &info);

    if (files[0] == -1)
    {
        write(1, "Error while opening the first file\n", strlen("Error while opening the first file\n"));
        close(files[0]);
        exit(23);
    }
    files[1] = open(dest_file, O_RDWR | O_CREAT, 0777);
    // state = link(origin_file, dest_file);
    //  if (files[1] == -1)
    /*if (state != 0)
    {
        perror("Error ");
        write(1, "\n", strlen("\n"));
        // close(files[1]);
        exit(23);
    }
    else
    {
        // change the permission of the destination file to be like the origin file
        chmod(dest_file, info.st_mode);
    }*/

    while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
        write(files[1], buffer, count);
}
int main(int argc, char **argv)
{
    if (argc == 3)
    {
        cp(argv[1], argv[2]);
        return 1;
    }
    else
    {
        write(1, "error in the number of arguments\n", strlen("error in the number of arguments\n"));
        return 0;
    }
}
