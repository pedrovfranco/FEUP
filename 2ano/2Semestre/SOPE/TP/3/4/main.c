#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#define MAX 50000


int a(int argc, char const *argv[])
{
	pid_t pid;

	pid = fork();

	if (pid > 0) // Parent
	{
		wait(NULL);
		printf("world !\n");		
	}
	else if (pid == 0)// Child
	{
		printf("Hello ");
	}
	else // Error
	{
		return 1;
	}
 	
 	return 0;
}


int b(int argc, char const *argv[])
{
	pid_t pid;

	pid = fork();

	if (pid > 0) // Parent
	{
		wait(NULL);
		printf("world !\n");		
	}
	else if (pid == 0)// Child
	{
		printf("Hello ");
	}
	else // Error
	{
		return 1;
	}
 	
 	return 0;
}


int main(int argc, char const *argv[])
{
	if (argv[1] == 0 || strcmp(argv[1], "a") == 0)
		return a(argc, argv);
	// else if (strcmp(argv[1], "c") == 0)
	// 	return c(argc, argv);
	// else if (strcmp(argv[1], "d") == 0)
	// 	return d(argc, argv);
		
	return 0;
}