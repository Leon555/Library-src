#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main()
{
	struct stat file_stat;
	
	stat("./ls.c", &file_stat);

	printf("modification time: %d\n", file_stat.st_mtime);

	exit(0);
}	
