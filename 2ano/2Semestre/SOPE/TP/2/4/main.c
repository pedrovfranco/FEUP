#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFFER_SIZE 50

int a(int argc, char const *argv[])
{
	int fd = open("ola", O_WRONLY | O_TRUNC | O_CREAT, 664);

	char name[BUFFER_SIZE] = "test";
	char class[BUFFER_SIZE] = "test";

	int i;
	for (i = 0; strcmp(name, "") != 0 && strcmp(class, "") != 0; i++)
	{
		printf("\nNome %u: ", i);
		scanf("%s", name);
		printf("\nClassificacao: ");
		scanf("%s", class);
		printf("\n");

		write(fd, name, strlen(name));
		write(fd , " ", 1);
		write(fd, class, strlen(class));
		write(fd , "\n", 1);
		
	}

	close(fd);

	return 0;
}


struct score
{
	char name[BUFFER_SIZE];
	char class[BUFFER_SIZE];
};

int b(int argc, char const *argv[])
{
	int fd = open("ola", O_WRONLY | O_TRUNC | O_CREAT, 775);

	char name[BUFFER_SIZE] = "test";
	char class[BUFFER_SIZE] = "test";

	int i;
	for (i = 0; strcmp(name, "") != 0 && strcmp(class, "") != 0; i++)
	{
		printf("\nNome %u: ", i);
		scanf("%s", name);
		printf("\nClassificacao: ");
		scanf("%s", class);
		printf("\n");

		write(fd, name, strlen(name));
		write(fd , " ", 1);
		write(fd, class, strlen(class));
		write(fd , "\n", 1);
		
	}

	close(fd);

	return 0;
}

int main(int argc, char const *argv[])
{

	return a(argc, argv);
}