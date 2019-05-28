#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unistd.h>

#include "node.h"

using namespace std;

vector<function<Node*(Node*)>> operations;

void initializeOperations()
{
	for (int i = 0; i < BRDWDTH; ++i)
	{
		function<Node*(Node*)> func = [i](Node* node)
		{
			Node* newNode = new Node(*node);
			
			if (!newNode->play(i))
			{
				delete newNode;
				return (Node*)NULL;
			}

			newNode->parent = node;

			return newNode;		
		};

		operations.push_back(func);
	}
}

Node* minimax(Node* currNode, int depth, bool maximizing)
{
	if (depth == 0)
		return currNode;

	Node* nextNode = NULL;
	Node* bestNode = NULL;
	int value;

	if (maximizing)
	{
		for (int i = 0; i < operations.size(); i++)
		{
			nextNode = operations[i](currNode);

			if (nextNode == NULL)
				continue;

			nextNode = minimax(nextNode, depth - 1, false);

			if (bestNode == NULL || nextNode->h > bestNode->h)
				bestNode = nextNode;
		}

		return bestNode;
	}
	else
	{
		for (int i = 0; i < operations.size(); i++)
		{
			nextNode = operations[i](currNode);

			if (nextNode == NULL)
				continue;

			nextNode = minimax(nextNode, depth - 1, true);
			
			if (bestNode == NULL || nextNode->h < bestNode->h)
				bestNode = nextNode;
		}

		return bestNode;
	}
}

void printBoard(vector<vector<int>> board)
{
	for (int i = 0; i < board.size(); ++i)
	{
		cout << "|";
		for (int j = 0; j < board[i].size(); ++j)
		{
			if (board[i][j] == 0)
				cout << " ";
			else
				cout << board[i][j];

			cout << " ";
		}

		cout << "|\n";
	}

	cout << " ";
	for (int i = 0; i < board.size()+1; ++i)
	{
		cout << "__";
	}
	
}


void gameLoop()
{
	int numPlays, winner;
	Node* currState = new Node();

	for (numPlays = 0; ; numPlays++)
	{
		printBoard(currState->state);
		cout << "\n\n";

		winner = currState->finished();

		if (winner)
		{
			cout << "Winner is " << winner << "\n";
			return;
		}

		if (numPlays % 2 == 0)
			cout << "Your turn\n\n";
		else
			cout << "Bot's turn\n\n";

		if (numPlays % 2 == 0)
		{
			string move;

			cout << "Choose a row: ";

			getline(cin, move);

			currState = operations[stoi(move)](currState);
		}
		else
		{
			Node* bestMove = minimax(currState, 3, true);

			while (!(*bestMove->parent == *currState))
			{
				bestMove = bestMove->parent;
			}

			currState = bestMove;

			usleep(1000*1000); //Sleeps for 1 second
		}

		
	}
}


int main()
{
	initializeOperations();

	gameLoop();


	return 0;
}