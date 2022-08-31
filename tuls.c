/*this program takes either 0 or 1 arguments
 * 
 */
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>

int main (int argc, char *argv[])
{
    if (argc == 1)
    {
        struct dirent **namelist;
           int n;

           n = scandir(".", &namelist, NULL, alphasort);
           if (n == -1) {
               perror("scandir");
               exit(EXIT_FAILURE);
           }
           
           while (n--) {
               printf("%s\n", namelist[n]->d_name);
               free(namelist[n]);
           }
           free(namelist);

           exit(EXIT_SUCCESS);
    } else {

    }
}
