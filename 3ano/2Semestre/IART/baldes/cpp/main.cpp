#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <functional>
#include <time.h> 

#include "node.cpp"

#define capacityA 4
#define capacityB 3

using namespace std;


void printSet(unordered_set<Node*, hashNode, hashNode> tree)
{
	for (auto it = tree.begin(); it != tree.end(); ++it)
	{
		cout << (**it) << "\n";
	}

	cout << "\n";
}

Node* breadth(vector<Node*> currRow, vector<int> objective, vector<function<vector<int>(vector<int>)>> operations, string operationNames[], int level)
{
	if (currRow.size() == 0)
	{
		return NULL;
	}

	Node* currNode = new Node();
	Node* nextNode = new Node();
	vector<int> operationHolder;

	vector<Node*> nextRow;

	// printSet(tree);
	while (1)
	{
		for (int i = 0; i < currRow.size(); i++)
		{
			currNode = currRow[i];

			for (int j = 0; j < operations.size(); j++)
			{
				operationHolder = operations[j](currNode->state);
				nextNode = new Node(operationHolder[0], operationHolder[1], currNode->cost+operationHolder[2]);
				nextNode->parent = currNode;
				nextNode->operationName = operationNames[j];

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

Node* breadth2(unordered_set<Node*, hashNode, hashNode> tree, vector<Node*> currRow, vector<int> objective, vector<function<vector<int>(vector<int>)>> operations, string operationNames[], int level)
{
	if (currRow.size() == 0)
	{
		cout << "Tree size = " << tree.size() << "\n";
		return NULL;
	}

	Node* currNode = new Node();
	Node* nextNode = new Node();
	vector<int> operationHolder;

	vector<Node*> nextRow;

	// printSet(tree);

	for (int i = 0; i < currRow.size(); i++)
	{
		currNode = currRow[i];

		for (int j = 0; j < operations.size(); j++)
		{
			operationHolder = operations[j](currNode->state);
			nextNode = new Node(operationHolder[0], operationHolder[1], currNode->cost+operationHolder[2]);
			nextNode->parent = currNode;
			nextNode->operationName = operationNames[j];

			if (nextNode->state == objective)
			{
				return nextNode;
			}

			if (tree.insert(nextNode).second)
			{
				nextRow.push_back(nextNode);
			}
		}
	}


	return breadth2(tree, nextRow, objective, operations, operationNames, level+1);
}


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


	vector<string> getPath(Node* node)
	{
		vector<string> path;

		while (node->parent != NULL) // Until reaches root node
		{
			path.push_back(node->operationName);

			node = node->parent;
		}

		string temp;
		for (int i = 0; i < path.size()/2; i++)
		{
			swap(path[i], path[path.size() - i - 1]);
		}

		return path;
	}

int main()
{
	function<vector<int>(vector<int>)> emptyA = [](vector<int> state) { int ret[3] = {0, state[1], 1}; return vector<int>(ret, ret+3);};
	function<vector<int>(vector<int>)> emptyB = [](vector<int> state) { int ret[3] = {state[0], 0, 1}; return vector<int>(ret, ret+3);};
	function<vector<int>(vector<int>)> fillA = [](vector<int> state) { int ret[3] = {capacityA, state[1], 1}; return vector<int>(ret, ret+3);};
	function<vector<int>(vector<int>)> fillB = [](vector<int> state) { int ret[3] = {state[0], capacityB, 1}; return vector<int>(ret, ret+3);};
	function<vector<int>(vector<int>)> pourAB = [](vector<int> state) { int ret[3]; ret[2] = 1; if (state[0] + state[1] > capacityB) { ret[0] = state[0] - (capacityB - state[1]); ret[1] = capacityB;} else { ret[0] = 0; ret[1] = state[0] + state[1];} return vector<int>(ret, ret+3);};
	function<vector<int>(vector<int>)> pourBA = [](vector<int> state) { int ret[3]; ret[2] = 1; if (state[0] + state[1] > capacityA) { ret[0] = capacityA; ret[1] = state[1] - (capacityA - state[0]);} else { ret[0] = state[0] + state[1]; ret[1] = 0;} return vector<int>(ret, ret+3);};

	vector<function<vector<int>(vector<int>)>> operations = {emptyA, emptyB, fillA, fillB, pourAB, pourBA};
	string operationNames[] = {"emptyA", "emptyB", "fillA", "fillB", "pourAB", "pourBA"};

	Node* rootNode = new Node(0,0,0);

	vector<Node*> rootRow;
	rootRow.push_back(rootNode);

	unordered_set<Node*, hashNode, hashNode> tree;
	tree.insert(rootNode);

	vector<int> objective = {2,0};

	Node* result = NULL;
	
	clock_t time = clock();

	for (int i = 0; i < 5000; i++)
	{
		result = breadth(rootRow, objective, operations, operationNames, 0);
		// result = breadth2(tree, rootRow, objective, operations, operationNames, 0);
		// result = depth(rootNode, objective, operations, operationNames, 0, 12);
	}
	
	double deltaTime = (double)(clock()-time)/CLOCKS_PER_SEC;

	vector<string> path = getPath(result);

	for (int i = 0; i < path.size(); i++)
	{
		cout << path[i] << "\n";
	}

	printf("\nFinished in : %f seconds.\n", deltaTime);

	return 0;
}