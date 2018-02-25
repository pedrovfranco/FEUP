#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFFER_SIZE 1024

int a(int argc, char const *argv[])
{
	int fd = open("ola", O_WRONLY | O_TRUNC | O_CREAT);

	char buffer[BUFFER_SIZE] = "";

	for (int i = 0;)
	{
		printf("\nNome%u:")
		numRead = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		write(fd, buffer, numRead);
		
		if (numRead != BUFFER_SIZE)
			break;
	}

	close(fd);

	return 0;
}

int b(int argc, char const *argv[])
{
	int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT);

	if (fd2 < 0)
		return 2;

	if (dup2(fd2, STDOUT_FILENO) < 0)
		return 3;

	int ret = a(argc, argv);

	close(f2);

	return ret;
}

int main(int argc, char const *argv[])
{

	return a(argc, argv);
}