#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

void CopyFile (char *source, char *destination)
{
    printf("source: %s\ndestination: %s", source, destination);
}

void getAbsoluteDestPath(char *dest, char *fileName)
{
    char buf[75];
    int buf_num = 2048;
    //check if path is relative or absolute
    if((dest[0] == '.') || dest[0] == '/'){
        dest = strcat(strchr(dest, '/'), fileName);
        dest = strcat(getcwd(buf, buf_num), dest);
    }else{
        dest = strcat(dest, fileName);
        char *absp = strcat(getcwd(buf, buf_num), "/");
        dest = strcat(absp, dest);
    }
    
    printf("\nabsolute path: %s\n", dest);
}

//this function takes in 2 arguments {[file name], [directory path]} copying the contents of the file to the given path
void ProcessTwoArguments(char **argv)
{
    struct dirent *dirEntry;
    DIR *workingDir = opendir(".");

    DIR *dir = opendir(argv[1]);
    if(dir){                                //if first entry is a directory
        printf("first argument must not be a directory.\n");
        exit(EXIT_FAILURE);
    }else if((dir = opendir(argv[2]))){     //if second entry is a directory
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
                realpath(dirEntry->d_name, sourcePath);
                match++;
                break;
            }
        }

        if(!match){             //if file doesn't exist
            perror("first argument");
            exit(EXIT_FAILURE);
        }
        
        printf("before dest");  
        //const int BUFFER = 1024;
        //char buf[75];
        getAbsoluteDestPath(argv[2], argv[1]);
        printf("\ndestination: %s\n", argv[2]);
        /*CopyFile(strcat(argv[1],
                    (strcat("/", getcwd(buf, BUFFER)))),  //get's the full path of the file given in the first argument
                 argv[2]);*/

    }else if(!dir){                         //if second entry is not a directory
        perror("second argument");
        exit(EXIT_FAILURE);            
    }else{                                  //if both entries are files
        /* if file entries are exactly the same, throw error
         * if file extensions are different, throw error
         * find first file
         * get it's path
         * find second file
         * get it's path
         * copy contents of first file into second file
         */

        if(strcmp(argv[1], argv[2])){
            printf("can't copy a file to itself");
        }
    }

    closedir(workingDir);
}

int main (int argc, char **argv)
{
    if(argc == 1 || argc == 2)  //if less than 2 entries sent to exe
    {
        printf("must supply arguments>1 (e.g. ./tucp [arg 1] [arg 2]...)\n");
    }else if (argc == 3){       //if only 2 entries sent to exe
        ProcessTwoArguments(argv);
    }else{                      //if x>2 entries sent to exe

    }
}