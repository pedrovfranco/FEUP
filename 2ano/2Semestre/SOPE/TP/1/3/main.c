#include "stdio.h"

int a(int argc, char const *argv[])
{
	printf("Hello !\n");
 	return 0; 
}

int b(int argc, char const *argv[])
{
	int i;
	for (i = 0; i < argc; ++i)
	{
		printf("%i : %s\n", i, argv[i]);
	}

	return argc;
}


int main(int argc, char const *argv[])
{

	return a(argc, argv);
}