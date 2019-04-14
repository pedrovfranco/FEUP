#include "interface.h"

#include <sstream> 
#include <algorithm>

#include "mapLoader.h"
#include "algorithms.h"

void menu()
{
	ui_utilities::ClearScreen();

	int input;

	cout << endl << "------------------------------------" << endl;
	cout << "|                                  |" << endl;
	cout << "|          N P U Z Z L E           |" << endl;
	cout << "|                                  |" << endl;
	cout << "------------------------------------" << endl;
	cout << "|      Choose the map to play  !   |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 1 - MAP 1                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 2 - MAP 2                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 3 - MAP 3                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << "| 4 - MAP 4                        |" << endl;
	cout << "------------------------------------" << endl;
	cout << endl << endl << "Option: ";

	string m = "maps/map";

	cin >> input;
	while (cin.fail() || input > 4 || input < 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nChoose a valid number please ! \n\n";
			cout << "Input: ";
			cin >> input;
		}


	if (input != 1)
		m += std::to_string(input);

	m += ".txt";
	
	agent(m);
}

int algorithm_menu()
{
	ui_utilities::ClearScreen();

	int input;

	cout << "------------------------------" << endl;
	cout << "|    Choose an algorithm:    |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 1 -      Breadth           |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 2 -       Depth            |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 3 - Iterative Deepening    |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 4 -    Uniform cost        |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 5 -       Greedy           |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 6 -         A*             |" << endl;
	cout << "------------------------------" << endl;
	cout << "| 0 -       Exit             |" << endl;
	cout << "------------------------------" << endl;

	cin >> input;
	while (cin.fail() || input > 6 || input < 0)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nChoose a valid number please ! \n\n";
			cout << "Option number: ";
			cin >> input;
		}

	return input;
}

void agent(std::string map)
{
	Node* rootNode = initiateMap(map);

	unordered_set<Node*, hashNode, hashNode> tree;
	tree.insert(rootNode);

	Node* result = NULL;
	
	int algorithm = algorithm_menu();

	int limit = 18;

	int heuristic = 1;

	if (algorithm == 2 || algorithm == 3 || algorithm == 5)
	{
		cout << "Insert a limit for the algorithm:";
		cin >> limit;
	}

	if (algorithm == 5 || algorithm == 6)
	{
		cout << "Choose between number of pieces out of place(0) or sum of manhattan distances(1):";
		cin >> heuristic;

		if (heuristic != 0 && heuristic != 1)
			heuristic = 0;
	}

	clock_t time = clock();

	if (algorithm == 1) result = breadth(rootNode);
	else if (algorithm == 2) result = depth(rootNode, 0, limit);
	else if (algorithm == 3) result = iteDeepening(rootNode, limit);
	else if (algorithm == 4) result = uniformCost(rootNode);
	else if (algorithm == 5) result = greedy(tree, rootNode, 0, limit, heuristic);
	else if (algorithm == 6) result = aStar2(rootNode, heuristic);
	else if (algorithm == 0) return;

	double deltaTime = (double)(clock()-time)/CLOCKS_PER_SEC;

	cout << "\n";

	if (result == NULL)
		cout << "Failed to find solution!";
	else
	{
		printPath(result);
		cout << "Agent's solution: " << result->cost << " moves.\n";
	}


	printf("\nFinished in %f seconds.\n", deltaTime);
}


void printPath(Node* node)
{
	if (node == NULL)
		return;

	vector<string> path;
	vector<Node*> nodes;

	while (node->parent != NULL) // Until reaches root node
	{
		path.push_back(node->operationName);
		nodes.push_back(node);

		node = node->parent;
	}

	cout << "Path:\n";
	cout << printState(node->state);
	cout << "\n\n";

	for (int i = path.size()-1; i >= 0; i--)
	{
		cout << path[i] << "\n";
		
		if (DEBUG)
			cout << *nodes[i];
		else
			cout << printState(nodes[i]->state);
		
		cout << "\n\n";
	}

}


void printMap(Node* node)
{
	for (int i = 0; i < node->state.size(); ++i)
	{
		for (int j = 0; j < node->state.size(); ++j)
		{
			cout << node->state[i][j] << " ";
		}

		cout << "\n";
	}
}

void printPath2(Node* node)
{
	if (node == NULL)
		return;

	vector<string> path;
	vector<Node*> nodes;

	while (node != NULL) // Until reaches root node
	{
		path.push_back(node->operationName);
		nodes.push_back(node);

		node = node->parent;
	}

	for (int i = path.size()-1; i >= 0; i--)
	{
		ui_utilities::ClearScreen();
		printMap(nodes[i]);
		cout << "\n\n";

		ui_utilities::milliSleep(1200); //sleeps for 1 second
	}
}
