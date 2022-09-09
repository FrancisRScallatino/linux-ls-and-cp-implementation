output: tucp.c
	gcc tucp.c -Wall -Werror -o tucp
gdb:
	gcc -g tucp.c -o tucpgdb
