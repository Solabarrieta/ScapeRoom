#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()

{   
    int fd=0;
    int count,totalChar = 0;
    char buffer[1024];
    fd= open("./.Jarvis/Help", O_RDONLY);
    if (-1==fd)
        {
            printf("open fail\n");
            return 0;
        }
    else
        {
            printf("fd = %d\n", fd);

        }

    for((count=read(fd, buffer, sizeof(buffer)))!=0){
        totalChar = totalChar + count;
    }

    lseek(fd, SEEK_SET, totalChar)
}