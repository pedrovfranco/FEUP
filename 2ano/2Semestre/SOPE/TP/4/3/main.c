#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

static int increasing = 1; // 1 == increasing, 0 == decreasing
static int value = 0;

void sigusr_handler(int signo)
{
	if (signo == SIGUSR1)
			increasing = 1;
	else if (signo == SIGUSR2)
		increasing = 0;
	else
		printf("Handler error!\n");
}


int a(int argc, char const *argv[])
{
	struct sigaction usraction;

	usraction.sa_handler = sigusr_handler;
	sigemptyset(&usraction.sa_mask);
	usraction.sa_flags = 0;

	if (sigaction(SIGUSR1, &usraction, NULL) != 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
		return 1;
	}

	if (sigaction(SIGUSR2, &usraction, NULL) != 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
		return 1;
	}


	while(1)
	{
		if (increasing)
			value++;
		else
			value--;

		printf("\n%i", value);

		sleep(1);
	}


	return 0;
}


int b(int argc, char const *argv[])
{
	struct sigaction usraction;

	usraction.sa_handler = sigusr_handler;
	sigemptyset(&usraction.sa_mask);
	usraction.sa_flags = 0;

	if (sigaction(SIGUSR1, &usraction, NULL) != 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
		return 1;
	}

	if (sigaction(SIGUSR2, &usraction, NULL) != 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
		return 1;
	}

	pid_t pid;
	pid = fork();


	unsigned int printCounter = 0;
	while (printCounter < 50)
	{

		if (increasing)
		{
			printCounter++;
			value++;
		}
		else
		{
			printCounter++;
			value--;
		}

		if (pid > 0) // Parent
		{
			if (increasing)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);

			if (printCounter >= 50)
				kill(pid, SIGTERM);
		}

		else if (pid == 0)// Child
		{
			printf("\n%i", value); 
			printCounter++;
		}

		else // Error
		{
			return 1;
		}

		sleep(1);

	}

	// if (pid > 0) //Parent
	// {
	// 	kill(pid, SIGTERM);
	// }

	return 0;
}

int main(int argc, char const *argv[])
{
	if (argv[1] == 0 || strcmp(argv[1], "a") == 0)
		return a(argc, argv);
	else if (strcmp(argv[1], "b") == 0)
		return b(argc, argv);
	// else if (strcmp(argv[1], "c") == 0)
	// 	return c(argc, argv);

	return 0;
}
