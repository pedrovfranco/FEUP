#include <iostream>
#include <vector>
#include <string>

#define BRDWDTH 7
#define BRDHGHT 6

using namespace std;



int board[BRDHGHT][BRDWDTH];
int currPlayer = 1;
int moveCounter = 0;


void initializeBoard()
{
	for (int i = 0; i < BRDHGHT; ++i)
	{
		for (int j = 0; j < BRDWDTH; ++j)
		{
			board[i][j] = 0;
		}
	}
}

void swapPlayer()
{
	currPlayer = (currPlayer)%2+1;
	moveCounter++;
}

void play(int x)
{
	int i;

	for (i = 0; i < BRDHGHT && board[i][x] == 0; ++i)
	{}
	i--;

	board[i][x] = currPlayer;
	swapPlayer();
}




int checkWinFour(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	if (board[y1][x1] != 0 && board[y1][x1] == board[y2][x2] && board[y1][x1] == board[y3][x3] && board[y1][x1] == board[y4][x4])
		return board[y1][x1];
	else
		return 0;
}

int checkWinHorizontal()
{
	for (int i = 0; i < BRDHGHT; ++i)
	{
		for (int j = 0; j < BRDWDTH-3; ++j)
		{
			int win = checkWinFour(j,i, j+1,i, j+2,i, j+3,i);
			if (win != 0)
				return win;
		}
	}

	return 0;
}

int checkWinVertical()
{
	for (int i = 0; i < BRDHGHT-3; ++i)
	{
		for (int j = 0; j < BRDWDTH; ++j)
		{
			int win = checkWinFour(j,i, j,i+1, j,i+2, j,i+3);
			if (win != 0)
				return win;
		}
	}

	return 0;
}

int checkWinDownRight()
{
	for (int i = 0; i < BRDHGHT-3; ++i)
	{
		for (int j = 0; j < BRDWDTH-3; ++j)
		{
			int win = checkWinFour(j,i, j,i+1, j,i+2, j,i+3);
			if (win != 0)
				return win;
		}
	}

	return 0;
}

int checkWinDownLeft()
{
	for (int i = 3; i < BRDHGHT; ++i)
	{
		for (int j = 0; j < BRDWDTH-3; ++j)
		{
			int win = checkWinFour(j,i, j,i+1, j,i+2, j,i+3);
			if (win != 0)
				return win;
		}
	}

	return 0;
}

void displayBoard()
{
	for (int i = 0; i < BRDHGHT; ++i)
	{
		for (int j = 0; j < BRDWDTH; ++j)
		{
			cout << board[i][j] << " ";
		}

		cout << "\n";
	}
}


int checkWin()
{
	int horizontal = checkWinHorizontal();
	if (horizontal != 0)
		return horizontal;

	int vertical = checkWinVertical();
	if (vertical != 0)
		return vertical;

	int downright = checkWinDownRight();
	if (downright != 0)
		return downright;

	int downleft = checkWinDownLeft();
	if (downleft != 0)
		return downleft;

	return 0;
}


int main()
{

	initializeBoard();

	displayBoard();

	cin.get();

	play(1);
	displayBoard();

	cin.get();

	play(0);
	displayBoard();

	return 0;
}