#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFFER_SIZE 1024

int a(int argc, char const *argv[])
{
	int fd = open(argv[1], O_RDONLY);

	char buffer[BUFFER_SIZE] = "";
	int numRead = BUFFER_SIZE;

	while(1)
	{
		numRead = read(fd, buffer, BUFFER_SIZE);
		write(STDOUT_FILENO, buffer, numRead);
		
		if (numRead != BUFFER_SIZE)
			break;
	}

	return 0;
}

int b(int argc, char const *argv[])
{
	int fd1 = open(argv[1], O_RDONLY);

	int fd2 = open(argv[2], O_WRONLY);

	if (dup2(fd2, STDOUT_FILENO) < 0)
		return 1;

	return a(argc, argv);
}

int main(int argc, char const *argv[])
{
	if (argv[1] == NULL)
	{
		printf("Format error!\n");
		return 1;
	}
	else if (argv[2] == NULL)
	{
		return a(argc, argv);
	}
	else if (argv[3] == NULL)
	{
		return b(argc, argv);
	}
	else
	{
		printf("Format error!\n");
		return 1;
	}

	return 1;
}