#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#define BUFFER_SIZE 50

int a(int argc, char const *argv[])
{
	char filename[] = "ola";

	int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 33204);

	char name[BUFFER_SIZE] = "test";
	char class[BUFFER_SIZE] = "test";

	int i;
	for (i = 0; strcmp(name, "") != 0 && strcmp(class, "") != 0; i++)
	{
		printf("\nNome %u: ", i);
		fgets(name, BUFFER_SIZE, stdin);
		printf("\nClassificacao: ");
		fgets(class, BUFFER_SIZE, stdin);
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
	int class;
};

int b(int argc, char const *argv[])
{
	FILE *fd = fopen("ola", "w+b");

	struct score temp;
	strcpy(temp.name, "temp");
	temp.class = 0;

	char buffer[1024];

	int i;
	for (i = 0; strcmp(temp.name, "-") != 0 && temp.class != -1; i++)
	{
		strcpy(temp.name, "-"); // Reset temp
		temp.class = -1;

		printf("\nNome %u: ", i);
		fgets(buffer, 1024, stdin);
		sscanf(buffer, "%s", &temp.name[0]);

		printf("Classificacao: ");
		fgets(buffer, BUFFER_SIZE, stdin);
		sscanf(buffer, "%i", &temp.class);

		if (strcmp(temp.name, "-") != 0 && temp.class != -1)
			fwrite(&temp, sizeof(temp), 1, fd);

	}

	fclose(fd);

	return 0;
}


int c(int argc, char const *argv[])
{
	FILE *fd = fopen("ola", "rb");

	struct score temp;
	strcpy(temp.name, "temp");
	temp.class = -1;

	int count = 1;

	int i;
	for (i = 0; count == 1; i++)
	{
		strcpy(temp.name, "-"); // Reset temp
		temp.class = -1;
		
		count = fread(&temp, sizeof(temp), 1, fd);
		
		if (strcmp(temp.name, "-") != 0 && temp.class != -1)
			printf("%s | %i\n", temp.name, temp.class);
	}
	printf("\n");

	fclose(fd);

	return 0;
}


int main(int argc, char const *argv[])
{
	if (argv[1] == 0)
	{
		printf("Wrong argument!\n");
		return 1;
	}
	if (strcmp(argv[1], "a") == 0)
		return a(argc, argv);
	else if (strcmp(argv[1], "b") == 0)
		return b(argc, argv);
	else if (strcmp(argv[1], "c") == 0)
		return c(argc, argv);
	
	return 1;	
}