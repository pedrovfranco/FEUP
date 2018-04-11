#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define STDERR 2
#define NUMITER 10000

void * thrfunc(void * arg)
{
	int i;
	fprintf(stderr, "Starting thread %s\n", (char *) arg);
	for (i = 1; i <= NUMITER; i++) write(STDERR,arg,1);
		return NULL;
}


int b1()
{
	pthread_t ta, tb;

	char firstArg = '1';
	char secondArg = '2';

	pthread_create(&ta, NULL, thrfunc, &firstArg);
	firstArg = '2';
	pthread_create(&tb, NULL, thrfunc, &firstArg);

	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	return 0;
}

int b2()
{
	pthread_t ta, tb;

	int firstArg = 1;
	int secondArg = 2;

	char *first;
	char *second;

	first = &firstArg;
	second = &secondArg;

	pthread_create(&ta, NULL, thrfunc, &first);
	pthread_create(&tb, NULL, thrfunc, &first);

	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc == 1)
		return b1();
	else if (argc == 2)
	{
		if (strcmp(argv[1], "1") == 0)
			return b1();
		else if (strcmp(argv[1], "2") == 0)
			return b2();
		else
			printf("Error!\n");
	}

	printf("Error!\n");
	return 1;
}