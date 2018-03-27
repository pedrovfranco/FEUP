#include "stdio.h"
#include <string.h>
#include <stdlib.h>

int ctoi(const char input)
{
	if (input >= '0' && input <= '9')
		return (input - '0');
	else
		return -1;
}


int a(int argc, char *argv[], char *envp[])
{
	int i;
	for (i = 0; envp[i] != NULL; i++)
	{
		printf("envp[%u] = %s\n", i, envp[i]);
	}

	return 0;
}

int b(int argc, char *argv[], char **envp)
{
	int i;
	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "USER", strlen("USER")) == 0)
		{
			printf("\nHello %s !\n", envp[i] + 5); // Prints after "USER="
			return 0;
		}
	}

	return 1; 
}

int c(int argc, char *argv[], char **envp)
{

	printf("\nHello %s !\n", getenv("USER"));

	return 0;
}

int d(int argc, char *argv[], char **envp)
{

	printf("\nHello %s !\n", getenv("USER_NAME"));

	return 0;
}

int main (int argc, char *argv[], char *envp[])
{

	return c(argc, argv, envp);
}