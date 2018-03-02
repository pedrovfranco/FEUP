/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}

void Labirinth::findLab(int x, int y, bool &res)
{
	if (res)
		return;

	if (y-1 > -1 && labirinth[y-1][x] == 1) //Up
	{
		if (!visited[y-1][x])
		{
			visited[y-1][x] = true;
			findLab(x, y-1, res);
		}
	}
	else if (labirinth[y-1][x] == 2)
	{
  		cout << "\nSucess!\n";
  		res = true;
  		return;
	}


	if (x+1 < 10 && labirinth[y][x+1] == 1) //Right
	{
		if (!visited[y][x+1])
		{
			visited[y][x+1] = true;
			findLab(x+1, y, res);
		}
	}
	else if (labirinth[y][x+1] == 2)
	{
		cout << "\nSucess!\n";
		res = true;
		return;
	}


	if (y+1 < 10 && labirinth[y+1][x] == 1) //Down
	{
		if (!visited[y+1][x])
		{
			visited[y+1][x] = true;
			findLab(x, y+1, res);
		}
	}
	else if (labirinth[y+1][x] == 2)
	{
		cout << "\nSucess!\n";
		res = true;
		return;
	}


	if (x-1 > -1 && labirinth[y][x-1] == 1) //Left
	{
		if (!visited[y][x-1])
		{
			visited[y][x-1] = true;
			findLab(x-1, y, res);
		}
	}
	else if (labirinth[y][x-1] == 2)
	{
		cout << "\nSucess!\n";
		res = true;
		return;
	}


}

bool Labirinth::findGoal(int x, int y)
{
	bool res = false;

	findLab(1,1,res);

	return res;
}

bool Labirinth::findGoal2(int x, int y)
{
	if (y-1 > -1) //Up
	{
		if (labirinth[y-1][x] == 1 && !visited[y-1][x])
		{
			visited[y-1][x] = true;
			return findGoal2(x, y-1);
		}
		else if (labirinth[y-1][x] == 2)
	  		return true;
	}

	if (x+1 < 10) //Right
	{
		if (labirinth[y][x+1] == 1 && !visited[y][x+1])
		{
			visited[y][x+1] = true;
			return findGoal2(x+1, y);
		}
		else if (labirinth[y][x+1] == 2)
	  		return true;
	}

	if (y+1 < 10) //Down
	{
		if (labirinth[y+1][x] == 1 && !visited[y+1][x])
		{
			visited[y+1][x] = true;
			return findGoal2(x, y+1);
		}
		else if (labirinth[y+1][x] == 2)
	  		return true;
	}

	if (x-1 > -1) //Left
	{
		if (labirinth[y][x-1] == 1 && !visited[y][x-1])
		{
			visited[y][x-1] = true;
			return findGoal2(x-1, y);
		}
		else if (labirinth[y][x-1] == 2)
	  		return true;
	}

	// Go back on dead end




	return false;
}
