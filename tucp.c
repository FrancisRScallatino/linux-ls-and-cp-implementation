#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main (int argc, char **argv)
{
    struct dirent *dirEntry;
    DIR *workingDir = opendir(".");

    if(argc == 1 || argc == 2)
    {
        perror("Must supply arguments>1 (e.g. ./tucp [arg 1] [arg 2]...)");
    }else if (argc == 3)
    {
        DIR *dir = opendir(argv[1]);
        if(dir){
            perror("First argument must not be a directory.");
            exit(EXIT_FAILURE);
        }else if((dir = opendir(argv[2]))){                     //if second entry is a directory
            /* find the file
             * if !exists throw error
             * else get file path
             * copy file to new path
             * if path !exists, make the subdirs and copy contents there
             * if file already exists, overwrite
             */
            short match = 0;        //file entry matches a file in working dir
            char sourcePath [256];  //path to to file being copied

            while((dirEntry = readdir(workingDir)) != NULL){
                if (strcmp(dirEntry -> d_name, argv[1]) == 0){
                    realpath(dirEntry -> d_name, sourcePath);
                    match++;
                    break;
                }
            }

            if(!match){
                perror("error with first argument");
                exit(EXIT_FAILURE);
            }
            
        }else{                                                  //if both entries are files
            /* if file entries are exactly the same, throw error
             * if file extensions are different, throw error
             * find first file
             * get it's path
             * find second file
             * get it's path
             * copy contents of first file into second file
             */
        }
    }else
    {

    }
}