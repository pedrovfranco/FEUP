#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <queue>
#include <functional>
#include <time.h> 
#include <algorithm>

#include "node.h"

#define N 4
#define DEBUG 1

using namespace std;


void printSet(unordered_set<Node*, hashNode, hashNode> tree)
{
	for (auto it = tree.begin(); it != tree.end(); ++it)
	{
		cout << (**it) << "\n";
	}

	cout << "\n";
}

vector<vector<int>> getObjective()
{
	vector<int> foobar(N, 0);
	vector<vector<int>> state(N, foobar);
	int counter = 1;
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			state[i][j] = counter;
			counter++;
		}
	}

	state[state.size()-1][state[0].size()-1] = 0;

	return state;
}

Node* breadth(vector<Node*> currRow, vector<vector<int>> objective, vector<function<Node*(Node*)>> operations, string operationNames[], int level)
{
	if (currRow.size() == 0)
	{
		return NULL;
	}

	Node* currNode = new Node();
	Node* nextNode = new Node();

	vector<Node*> nextRow;

	while (1)
	{
		for (int i = 0; i < currRow.size(); i++)
		{
			currNode = currRow[i];
			// cout << *currNode << "\n";

			for (int j = 0; j < operations.size(); j++)
			{
				nextNode = operations[j](currNode);
				nextNode->cost++;
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[j];

				// cout << *nextNode << "\n";

				if (nextNode->state == objective)
				{
					return nextNode;
				}

				if (nextNode->parent == NULL || nextNode->state != nextNode->parent->state) // Checks if the state is the same after the operation
				{
					if (nextNode->parent->parent == NULL || nextNode->state != nextNode->parent->parent->state) // Checks if the state doesn't change from 2 levels above
					{
						nextRow.push_back(nextNode);
					}
				}
			}
		}

		currRow = nextRow;
		nextRow.resize(0);
	}


	return NULL;
}


Node* breadth2(unordered_set<Node*, hashNode, hashNode> tree, vector<Node*> currRow, vector<vector<int>> objective, vector<function<Node*(Node*)>> operations, string operationNames[], int level)
{
	if (currRow.size() == 0)
	{
		cout << "Tree size = " << tree.size() << "\n";
		return NULL;
	}

	// cout << "Level  = " << level << ", Tree size = " << tree.size() << "\n";

	Node* currNode;
	Node* nextNode;
	vector<int> operationHolder;

	vector<Node*> nextRow;

	for (int i = 0; i < currRow.size(); i++)
	{
		currNode = currRow[i];

		if (DEBUG)
			cout << *currNode << "\n";

		for (int j = 0; j < operations.size(); j++)
		{
			nextNode = operations[j](currNode);
			nextNode->cost++;
			nextNode->parent = currNode;
			nextNode->operationName = operationNames[j];

			if (DEBUG)
				cout << *nextNode << "\n";


			if (nextNode->state == objective)
			{
				return nextNode;
			}

			if (tree.insert(nextNode).second)
			{
				nextRow.push_back(nextNode);
			}
			else
			{
				delete nextNode;
			}
		}
	}


	return breadth2(tree, nextRow, objective, operations, operationNames, level+1);
}


Node* breadth3(unordered_set<Node*, hashNode, hashNode> tree, priority_queue<Node*, vector<Node*>, sortH> currRow, vector<vector<int>> objective, vector<function<Node*(Node*)>> operations, string operationNames[], int level)
{
	if (currRow.size() == 0)
	{
		cout << "Tree size = " << tree.size() << "\n";
		return NULL;
	}

	// cout << "Level  = " << level << ", Tree size = " << tree.size() << "\n";

	Node* currNode;
	Node* nextNode;

	priority_queue<Node*, vector<Node*>, sortH> nextRow;

	for (; currRow.size() > 0;)
	{
		currNode = currRow.top();

		if (DEBUG)
			cout << *currNode << "\n";

		for (int j = 0; j < operations.size(); j++)
		{
			nextNode = operations[j](currNode);
			nextNode->cost++;
			nextNode->parent = currNode;
			nextNode->operationName = operationNames[j];

			if (DEBUG)
				cout << *nextNode << "\n";


			if (nextNode->state == objective)
			{
				return nextNode;
			}

			if (tree.insert(nextNode).second)
			{
				nextNode->setH(objective);
				nextRow.push(nextNode);
			}
		}

		currRow.pop();
	}


	return breadth3(tree, nextRow, objective, operations, operationNames, level+1);
}


/*
Node* depth(Node* currNode, vector<int> objective, vector<function<vector<int>(vector<int>)>> operations, string operationNames[], int level, int limit)
{
	if (currNode == NULL)
	{
		return NULL;
	}

	Node* nextNode = new Node();
	vector<int> operationHolder;

	vector<Node*> nextRow;

	// printSet(tree);
	for (int i = 0; i < operations.size(); i++)
	{
		operationHolder = operations[i](currNode->state);
		nextNode = new Node(operationHolder[0], operationHolder[1], currNode->cost+operationHolder[2]);
		nextNode->parent = currNode;
		nextNode->operationName = operationNames[i];

		if (nextNode->state == objective)
		{
			return nextNode;
		}

		if (nextNode->parent == NULL || nextNode->state != nextNode->parent->state) // Checks if the state is the same after the operation
		{
			if (nextNode->parent->parent == NULL || nextNode->state != nextNode->parent->parent->state) // Checks if the state doesn't change from 2 levels above
			{
				if (level+1 <= limit)
				{
					Node* nextCall = depth(nextNode, objective, operations, operationNames, level+1, limit);

					if (nextCall != NULL)
						return nextCall;
				}
			}
		}
	}


	return NULL;
}

*/




Node* greedy(unordered_set<Node*, hashNode, hashNode>& tree, Node* currNode, vector<vector<int>> objective, vector<function<Node*(Node*)>> operations, string operationNames[], int level)
{
	if (currNode == NULL/* || level == 10*/)
	{
		return new Node();
	}

	if (DEBUG)
	{
		cout << "h = " << currNode->h << "\n";
		cout << *currNode << "\n\n";
	}

	Node* nextNode;

	priority_queue<Node*, vector<Node*>, sortH> nextRow;

	for (int i = 0; i < operations.size(); i++)
	{
		nextNode = operations[i](currNode);
		nextNode->cost++;
		nextNode->parent = currNode;
		nextNode->operationName = operationNames[i];

		if (nextNode->state == objective)
		{ 
			return nextNode;
		}

		if (tree.insert(nextNode).second)
		{
			nextNode->setH(objective);
			nextRow.push(nextNode);
		}
	}

	while (nextRow.size() > 0)
	{
		nextNode = nextRow.top();

		// if (DEBUG)
		// {
		// 	cout << "h = " << nextNode->h << "\n";
		// 	cout << *nextNode << "\n\n";
		// }

		Node* nextCall = greedy(tree, nextNode, objective, operations, operationNames, level+1);

		if (nextCall != NULL)
			return nextCall;

		nextRow.pop();
	}


	return NULL;
}


multiset<Node*, sortH>::iterator linearSearchSet(multiset<Node*, sortH> input, Node* node)
{
	for (auto it = input.begin(); it != input.end(); ++it)
	{
		if ((*it)->state == node->state)
			return it;
	}

	return input.end();
}


Node* aStar(vector<vector<int>> objective, vector<function<Node*(Node*)>> operations, string operationNames[], int level)
{
	multiset<Node*, sortH> openList;
	multiset<Node*, sortH> closedList;
	
	Node* currNode = new Node(N);
	currNode->setH(objective);
	openList.insert(currNode);

	Node* nextNode;

	bool added;
	int i = 0;
	while (openList.size() > 0)
	{
		multiset<Node*, sortH>::iterator it = openList.begin();
		// it--;

		currNode = *(it);
		openList.erase(it);

		closedList.insert(currNode);

		cout << *currNode << "\n";

		added = false;

		for (int i = 0; i < operations.size(); i++)
		{
			nextNode = operations[i](currNode);
			nextNode->cost++;
			nextNode->parent = currNode;
			nextNode->operationName = operationNames[i];
			nextNode->setH(objective);

			if (nextNode->state == objective)
			{ 
				return nextNode;
			}
			
			it = find(closedList.begin(), closedList.end(), nextNode);

			if (nextNode->state != currNode->state && it == closedList.end())
			{
				it = find(openList.begin(), openList.end(), nextNode);
				
				if (it == openList.end())
				{
					openList.insert(nextNode);
				}
				else
				{
					if (nextNode->cost < (*it)->cost)
					{
						openList.erase(it);
						openList.insert(nextNode);
					}
				}
			}
			
		}

		i++;

		// if (i == 10)
		// {
		// 	return NULL;
		// }
		// 
		// cout << openList.size() << "\n";
	}

	return NULL;
}


void printPath(Node* node)
{
	vector<string> path;
	vector<vector<vector<int>>> states;

	while (node->parent != NULL) // Until reaches root node
	{
		path.push_back(node->operationName);
		states.push_back(node->state);

		node = node->parent;
	}

	cout << printState(node->state);
	cout << "\n\n";

	for (int i = path.size()-1; i >= 0; i--)
	{
		cout << path[i] << "\n";
		cout << printState(states[i]);
		cout << "\n\n";
	}

}


int main()
{
	function<Node*(Node*)> up = [](Node* node) { Node* newNode = new Node(*node); if(newNode->y > 0) { swap(newNode->state[newNode->y][newNode->x], newNode->state[newNode->y-1][newNode->x]); newNode->y--;} return newNode;};
	function<Node*(Node*)> right = [](Node* node) { Node* newNode = new Node(*node); if(newNode->x < newNode->state[0].size()-1) { swap(newNode->state[newNode->y][newNode->x], newNode->state[newNode->y][newNode->x+1]); newNode->x++;} return newNode;};
	function<Node*(Node*)> down = [](Node* node) { Node* newNode = new Node(*node); if(newNode->y < newNode->state.size()-1) { swap(newNode->state[newNode->y][newNode->x], newNode->state[newNode->y+1][newNode->x]); newNode->y++;} return newNode;};
	function<Node*(Node*)> left = [](Node* node) { Node* newNode = new Node(*node); if(newNode->x > 0) { swap(newNode->state[newNode->y][newNode->x], newNode->state[newNode->y][newNode->x-1]); newNode->x--;} return newNode;};

	vector<function<Node*(Node*)>> operations = {up, right, down, left};
	string operationNames[] = {"up", "right", "down", "left"};

	vector<vector<int>> objective = getObjective();

	Node* rootNode = new Node(N);
	rootNode->setH(objective);

	vector<Node*> rootRow;
	rootRow.push_back(rootNode);

	priority_queue<Node*, vector<Node*>, sortH> rootRow2;
	rootRow2.push(rootNode);

	unordered_set<Node*, hashNode, hashNode> tree;
	tree.insert(rootNode);

	Node* result = NULL;
	
	clock_t time = clock();

	for (int i = 0; i < 1; i++)
	{
		// result = breadth(rootRow, objective, operations, operationNames, 0);
		// result = breadth2(tree, rootRow, objective, operations, operationNames, 0);
		// result = breadth3(tree, rootRow2, objective, operations, operationNames, 0);
		// result = depth(rootNode, objective, operations, operationNames, 0, 12);
		// result = greedy(tree, rootNode, objective, operations, operationNames, 0);
		result = aStar(objective, operations, operationNames, 0);
	}
	
	double deltaTime = (double)(clock()-time)/CLOCKS_PER_SEC;

	cout << "\n";
	printPath(result);

	printf("\nFinished in : %f seconds.\n", deltaTime);

	return 0;
}