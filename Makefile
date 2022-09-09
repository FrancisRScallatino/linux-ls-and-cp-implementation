CFLAGS := -Wall -Werror

output: tucp.c
	gcc tucp.c $(CFLAGS) -o tucp
run: tucp
	./tucp $(var) $(var)
debug: tucp.c
	gcc -g tucp.c -o tucpgdb
