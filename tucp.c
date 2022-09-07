#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main (int argc, char **argv)
{
    if(argc == 1 || argc == 2)
    {
        perror("Must supply arguments>1 (e.g. ./tucp [arg 1] [arg 2]...)");
    }else if (argc == 3)
    {
        DIR *dir = opendir(argv[1]);
        if(dir){
            perror("First argument must not be a directory.");
            exit(EXIT_FAILURE);
        }
    }else
    {

    }
}