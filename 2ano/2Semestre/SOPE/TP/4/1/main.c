#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void sigint_handler(int signo)
{
	printf("In SIGINT handler ...\n");
}

int a(int argc, char const *argv[])
{
	if (signal(SIGINT,sigint_handler) < 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
		return 1;
	}
	printf("Sleeping for 30 seconds ...\n");
	sleep(30);
	printf("Waking up ...\n");
	return 0;
}

int b(int argc, char const *argv[])
{
	if (signal(SIGINT, sigint_handler) < 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
		return 1;
	}
	int time = 10;
	printf("Sleeping for %u seconds ...\n", time);

	while (time > 0)
	{
		time = sleep(time);
	}

	printf("Waking up ...\n");
	return 0;
}


int c(int argc, char const *argv[])
{
	struct sigaction sigact;

	sigact.sa_handler = sigint_handler;
   sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;

	if (sigaction(SIGINT, &sigact, NULL) != 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
		return 1;
	}

	int time = 10;
	printf("Sleeping for %u seconds ...\n", time);

	while (time > 0)
	{
		time = sleep(time);
	}

	printf("Waking up ...\n");
	return 0;
}


int main(int argc, char const *argv[])
{
	if (argv[1] == 0 || strcmp(argv[1], "a") == 0)
		return a(argc, argv);
	else if (strcmp(argv[1], "b") == 0)
		return b(argc, argv);
	else if (strcmp(argv[1], "c") == 0)
		return c(argc, argv);

	return 0;
}
