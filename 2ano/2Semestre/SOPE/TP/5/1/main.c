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

struct pair {
	int first;
	int second;
};


int b(void)
{
	int pipedes[2]; // pipedes[0] = read, pipedes[1] = write
	pid_t pid;
	struct pair myPair;

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
		scanf("%i", &myPair.first);
		printf("Enter the second number : ");
		scanf("%i", &myPair.second);

		write(pipedes[1], &myPair, sizeof(struct pair));

		close(pipedes[1]);
	}
	else if (pid == 0) // Child
	{
		close(pipedes[1]);

		read(pipedes[0], &myPair, sizeof(struct pair));

		printf("%i\n%i\n%i\n%f\n", myPair.first+myPair.second, myPair.first-myPair.second, myPair.first*myPair.second, (double)myPair.first/myPair.second);

		close(pipedes[0]);
	}
	else // Fork error
	{
		printf("\nFork error!\n");
		return 1;
	}

	return 0;
}


int c(void)
{
	int pipedes[2]; // pipedes[0] = read, pipedes[1] = write
	pid_t pid;
	char strArray[2][5];

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
		scanf("%s", strArray[0]);
		printf("Enter the second number : ");
		scanf("%s", strArray[1]);

		write(pipedes[1], &strArray, 2*5);

		close(pipedes[1]);
	}
	else if (pid == 0) // Child
	{
		close(pipedes[1]);

		read(pipedes[0], &strArray, 2*5);

		int first = strtol(strArray[0], NULL, 10), second = strtol(strArray[1], NULL, 10);

		printf("%i\n%i\n%i\n%f\n", first+second, first-second, first*second, (double)first/second);

		close(pipedes[0]);
	}
	else // Fork error
	{
		printf("\nFork error!\n");
		return 1;
	}
	
	return 0;
}


int main(const int argc, const char* argv[])
{

	if (argc > 2)
		return 1;
	else if (argc == 1)
		return a();
	else
	{
		if (strcmp(argv[1], "a") == 0)
			return a();

		if (strcmp(argv[1], "b") == 0)
			return b();

		if (strcmp(argv[1], "c") == 0)
			return c();
	}

	return 1;
}	
