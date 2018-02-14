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

char* getName(int argc, char const *argv[])
{
	int charCounter = 0;

	int i;
	for (i = 1; i < argc-1; ++i)
	{
		charCounter += strlen(argv[i]);
		charCounter++;
	}

	char* ret = malloc(charCounter);
	int current = 0;

	for (i = 1; i < argc-1; ++i)
	{
		*(ret + current) = ' ';
		current++;

		strcpy(ret + current, argv[i]);
		current += strlen(argv[i]);
	}

	return ret;
}

int a(int argc, char const *argv[])
{
	printf("Hello");

	int i;
	for (i = 1; i < argc; ++i)
	{
		printf(" %s", argv[i]);
	}
	printf(" !\n\n");

 	return 0;
}

int b(int argc, char const *argv[])
{
	char* name = getName(argc, argv);

	int i;
	for (i = 0; i < ctoi(argv[argc-1][0]); ++i)
	{
		printf("\nHello%s !\n", name);
	}

	return 0;
}

int main(int argc, char const *argv[])
{

	return b(argc, argv);
}