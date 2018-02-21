#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdint.h>
#include <stddef.h>
#include <wchar.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>


#define BUFFER_SIZE 1024

int a(int argc, char const *argv[])
{
	FILE *fp1 = fopen(argv[1], "r");
	
	if (fp1 == NULL)
		return 1;

	FILE *fp2 = fopen(argv[2], "w");

	char buffer[BUFFER_SIZE] = "";
	int numRead = BUFFER_SIZE;

	while(1)
	{
		numRead = fread(buffer, sizeof(char), BUFFER_SIZE, fp1);
		fwrite(buffer, sizeof(char), numRead, fp2);
		
		if (numRead != BUFFER_SIZE)
			break;
	}

	return 0;
}

int b(int argc, char const *argv[])
{
	int fd1 = open(argv[1], O_RDONLY);

	struct stat fileStat;
	if (stat(argv[1],&fileStat) < 0)    
        return 1;

	int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, fileStat.st_mode);

	char buffer[BUFFER_SIZE] = "";
	int numRead = BUFFER_SIZE;

	while(1)
	{
		numRead = read(fd1, buffer, BUFFER_SIZE);
		write(fd2, buffer, numRead);
		
		if (numRead != BUFFER_SIZE)
			break;
	}

	return 0;
}

int c(int argc, char const *argv[])
{
	clock_t begin = clock();
	
	int ret;

	ret = a(argc, argv);

	clock_t end = clock();

	float time_elapsed = (float)(end - begin) / CLOCKS_PER_SEC;

	printf("\nTime spent: %f seconds\n\n", time_elapsed);

	return ret;
}

int main(int argc, char const *argv[])
{
	if (argv[1] == NULL || argv[2] == NULL)
	{
		printf("Must contain 2 files!\n");
		return 1;
	}

	return c(argc, argv);
}