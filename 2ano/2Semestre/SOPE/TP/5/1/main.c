#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>



int a(void)
{
	int pipedes[2]; // pipedes[0] = read, pipedes[1] = write
	pid_t pid;
	int inputNumbers[2];

	if (pipe(pipedes) != 0) // Pipe error
	{
		printf("\nPipe error!\n");
		return 1;
	}

	pid = fork();

	if (pid > 0) // Parent
	{
		close(pipedes[0]);

		printf("Enter the first number : ");
		scanf("%i", &inputNumbers[0]);
		printf("Enter the second number : ");
		scanf("%i", &inputNumbers[1]);

		write(pipedes[1], inputNumbers, 2*sizeof(int));

		close(pipedes[1]);
	}
	else if (pid == 0) // Child
	{
		close(pipedes[1]);

		read(pipedes[0], inputNumbers, 2*sizeof(int));

		printf("%i\n%i\n%i\n%f\n", inputNumbers[0]+inputNumbers[1], inputNumbers[0]-inputNumbers[1], inputNumbers[0]*inputNumbers[1], (double)inputNumbers[0]/inputNumbers[1]);

		close(pipedes[0]);
	}
	else // Fork error
	{
		printf("\nFork error!\n");
		return 1;
	}

	return 0;
}



int main(void)
{

	return a();
}
