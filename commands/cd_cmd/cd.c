#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../pwd_cmd/pwd.c"

void cd(char *path)
{
    char* msg_eaccess="The search permission is denied for one of the components of path.\n";
    char* msg_namelong="The path is too long.\n";
    char* msg_notexist="The file does not exist.\n";

    if(chdir(path)!=0)
	{
        if(errno==EACCES)
            write(1,msg_eaccess,strlen(msg_eaccess));
        else if(errno==ENAMETOOLONG)
            write(1,msg_namelong,strlen(msg_namelong));
        else if(errno==ENOENT)
            write(1,msg_notexist,strlen(msg_notexist));
        else
            write(1,"ERROR !!!",10);

	}

}

int main(int argc, char *argv[])
{
    if(argc==2)
    {
         pwd();
         cd(argv[1]);
         pwd();
         return 1;
    }
    else
    {
        write(1,"Error : pwd should have only one arguments\n",55);
        return 0;
    }
}
