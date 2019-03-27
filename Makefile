CC = gcc

microshell: microshell.c
	$(CC) microshell.c -o microshell
clean:
	rm -f microshell *.o