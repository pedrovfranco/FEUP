#include <termios.h>
#include <unistd.h>
#include <string.h> 
#include <stdio.h>

#define MAX_PASSWORD_LENGTH 25


int main(void)
{
	char password[MAX_PASSWORD_LENGTH+1], temp[] = "\nInsert password please: ";
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	write(STDOUT_FILENO, &temp, strlen(temp));

	int i;
	for (i = 0; i < MAX_PASSWORD_LENGTH && password[i-1] != '\n' ;i++)
	{
		read(STDIN_FILENO, &password[i], 1);
		write(STDOUT_FILENO, "*", 1);
	}
	password[i] = 0;

	printf("\nPassword = %s", password);

	return 0;
}