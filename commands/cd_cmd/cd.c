#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
//#include "cd.h"
//#include "../pwd_cmd/pwd.c"

int cd(char *path)
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
            write(1,"ERROR !!!\n",10);

            return 0;

	}
	return 1;

}

/* int main(int argc, char *argv[])
{
    if(argc==2)
    {
        // pwd();
         cd(argv[1]);

         char current_directory[256];
    getcwd(current_directory,sizeof(current_directory));

    write(1,"you are in : ",12);

    write(1,current_directory,strlen(current_directory));

        // pwd();
         return 1;
    }
    else
    {
        write(1,"Error : cd should have one argument\n",40);
        return 0;
    }
}*/
