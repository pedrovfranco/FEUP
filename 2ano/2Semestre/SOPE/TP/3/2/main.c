#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int global = 1;

int a(int argc, char const *argv[])
{
	write(STDOUT_FILENO,"1",1);

	int p = fork();

	if (p < 0) // Error
	{
		return 1;
	}
	else if (p > 0)
	{
		write(STDOUT_FILENO,"2",1);
		write(STDOUT_FILENO,"3",1);
	}
	else
	{
		write(STDOUT_FILENO,"4",1);
		write(STDOUT_FILENO,"5",1);
	}
	write(STDOUT_FILENO,"\n",1);
	
	return 0;
}

int c(int argc, char const *argv[])
{
	printf("1");

	int p = fork();

	if (p < 0) // Error
	{
		return 1;
	}
	else if (p > 0)
	{
		printf("2");
		printf("3");
	}
	else
	{
		printf("4");
		printf("5");
	}
	printf("\n");
	
	return 0;
}

int d(int argc, char const *argv[])
{
	printf("1\n");

	int p = fork();

	if (p < 0) // Error
	{
		return 1;
	}
	else if (p > 0)
	{
		printf("2");
		printf("3");
	}
	else
	{
		printf("4");
		printf("5");
	}
	printf("\n");
	
	return 0;
}



int main(int argc, char const *argv[])
{
	if (argv[1] == 0 || strcmp(argv[1], "a") == 0)
		return a(argc, argv);
	else if (strcmp(argv[1], "c") == 0)
		return c(argc, argv);
	else if (strcmp(argv[1], "d") == 0)
		return d(argc, argv);
	
	return 1;	
}