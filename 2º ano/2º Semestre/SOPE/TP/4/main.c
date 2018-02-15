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


int a(int argc, char const *argv[])
{
	printf("\nHello %s !\n\n", argv[1]);

 	return 0;
}

int b(int argc, char const *argv[])
{
	int i;
	for (i = 0; i < ctoi(argv[argc-1][0]); ++i)
	{
		printf("\nHello %s !\n", argv[1]);
	}
	printf("\n");
	
	return 0;
}

int main(int argc, char const *argv[])
{

	return b(argc, argv);
}