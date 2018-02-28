#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int global = 1;

int a(int argc, char const *argv[])
{
	int local = 2;
	
	if(fork() > 0)
	{
		printf("PID = %d; PPID = %d\n", getpid(), getppid());
		global++;
		local--;
	}
	else
	{
		printf("PID = %d; PPID = %d\n", getpid(), getppid());
		global--;
		local++;
	}
	printf("PID = %d - global = %d ; local = %d\n", getpid(), global, local);
	
	return 0;
}


int main(int argc, char const *argv[])
{

	return a(argc, argv);	
}