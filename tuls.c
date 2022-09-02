/*this program takes either 0 or 1 arguments
 * if 0 arguments simply outputs list of files/dirs to stdout
 * if 1 argument, recursively outputs all files/dirs located inside given dir
 */
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

void recursiveList (char *basePath)
{
    char path [256];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    //base case
    //cannot open directory
    if (!dir){
        return;
    }

    //loop until there's no file to be read
    while((dp = readdir(dir)) != NULL)
    {
        //if dir name is not the working or parent directory
        if(strcmp(dp -> d_name, ".") != 0 && strcmp(dp -> d_name, "..") != 0)
        {
            //printf("made it past the if\n");
            printf("%s\n", dp -> d_name);

            //make new, deeper path from base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp -> d_name);

            recursiveList(path);
        }
    }

    closedir(dir);
}

int main (int argc, char *argv[])
{
    if (argc == 1)
    {
        struct dirent **namelist;   //used to hold names of files/dirs
        int n;                      //file/dir count

        //scans current dir and returns with the number of files located
        //also fills namelist with the names of each file found
        n = scandir(".", &namelist, NULL, alphasort);
        if (n == -1) {
            perror("scandir");
            exit(EXIT_FAILURE);
        }
        
        int i = 0;
        while (i<n) {
            printf("%s\n", namelist[i]->d_name);
            free(namelist[i++]);
        }
        free(namelist);

        exit(EXIT_SUCCESS);
    } else {
        recursiveList(argv[1]);
    }
}