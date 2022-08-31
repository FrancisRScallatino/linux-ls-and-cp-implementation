/*this program takes either 0 or 1 arguments
 * if 0 arguments simply outputs list of files/dirs to stdout
 * if 1 argument, recursively outputs all files/dirs located inside given dir
 */
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>

int main (int argc, char *argv[])
{
    if (argc == 1)
    {
        struct dirent **namelist;   //used to hold names of files/dirs
        int n;                      //file/dir count

        //scans current dir and returns with the number of files located
        n = scandir(".", &namelist, NULL, alphasort);
        if (n == -1) {
            perror("scandir");
            exit(EXIT_FAILURE);
        }
        
        //prints files/dirs in current dir in order (first to last)
        int i = 0;
        while (i<n) {
            printf("%s\n", namelist[i]->d_name);
            free(namelist[i++]);
        }
        free(namelist);

        exit(EXIT_SUCCESS);
    } else {

    }
}