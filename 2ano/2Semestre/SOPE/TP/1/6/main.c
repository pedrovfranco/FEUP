#include "stdio.h"
#include <string.h>
#include <stdlib.h>

#define BUF_LENGTH 256

int ctoi(const char input)
{
	if (input >= '0' && input <= '9')
		return (input - '0');
	else
		return -1;
}


int a()
{
	FILE *src, *dst;
	char buf[BUF_LENGTH];

	if ((src = fopen("infile.txt", "r")) == NULL)
	{
		return 1; // infile.txt not found
	}
	if ((dst = fopen("outfile.txt", "w")) == NULL)
	{
		return 2; // outfile.txt not found
	} 

	while ((fgets(buf, BUF_LENGTH, src)) != NULL)
	{
		fputs(buf, dst);
	}

	fclose(src);
	fclose(dst);
	
	return 0; // Sucess
}


int main()
{
	
	return a();
}