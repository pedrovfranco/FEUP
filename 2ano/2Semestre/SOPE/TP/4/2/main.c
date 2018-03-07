#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void sigint_handler(int signo)
{
 printf("Entering SIGINT handler ...\n");
 sleep(5);
 printf("Exiting SIGINT handler ...\n");
}

void sigterm_handler(int signo)
{
 printf("Entering SIGTERM handler ...\n");
 printf("Exiting SIGTERM handler ...\n");
}

int a(int argc, char const *argv[])
{
	struct sigaction action;

	action.sa_handler = sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	if (sigaction(SIGINT,&action,NULL) < 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
		return 1;
	}

	printf("Try me with CTRL-C ...\n");
	while(1)
	{
		pause();
	}

	return 0;
}

int c(int argc, char const *argv[])
{
	struct sigaction sigintaction;

	sigintaction.sa_handler = sigint_handler;
	sigemptyset(&sigintaction.sa_mask);
	sigintaction.sa_flags = 0;

	if (sigaction(SIGINT,&sigintaction,NULL) < 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
		return 1;
	}

	struct sigaction sigtermaction;

	sigtermaction.sa_handler = sigterm_handler;
	sigemptyset(&sigtermaction.sa_mask);
	sigtermaction.sa_flags = 0;

	if (sigaction(SIGTERM,&sigtermaction,NULL) < 0)
	{
		fprintf(stderr,"Unable to install SIGTERM handler\n");
		return 1;
	}

	printf("Try me with CTRL-C ...\n");
	while(1)
	{
		pause();
	}

	return 0;
}


int main(int argc, char const *argv[])
{
	if (argv[1] == 0 || strcmp(argv[1], "a") == 0)
		return a(argc, argv);
	// else if (strcmp(argv[1], "b") == 0)
	// 	return b(argc, argv);
	else if (strcmp(argv[1], "c") == 0)
		return c(argc, argv);

	return 0;
}
