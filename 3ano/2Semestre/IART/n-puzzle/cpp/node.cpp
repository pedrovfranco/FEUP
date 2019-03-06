#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

class Node
{
public:
	vector<vector<int>> state;
	int x;
	int y;
	int cost;
	int level;
	Node* parent = NULL;
	string operationName = "";

	Node()
	{

	}

	Node(int n)
	{
		this->cost = 0;

		unordered_set<int> set;

		for (int i = 0; i < n; i++)
		{
			state.push_back(vector<int>());

			for (int j = 0; j < n; j++)
			{
				int randNum = rand()%(n*n);
				if (set.insert(randNum).second)
				{
					state[i].push_back(randNum);
				}
			}
		}
	}

	Node(const Node& node)
	{
		this->state = node.state;

		this->x = node.x;
		this->y = node.y;

		this->cost = node.cost;
	}
	
	bool operator==(const Node* node) const
	{
		return (this->state == node->state);
	}

	bool operator==(const Node& node) const
	{
		return (this->state == node.state);
	}
};

// ostream& operator<<(ostream& os, const Node& node)
// {
// 	return (os << "Node {state=[" << node.state[0] << ", " << node.state[1] << "], " << "cost = " << node.cost);
// }

struct hashNode
{
	int operator() (const Node* node) const
	{
		int hash = 0;

		for (int i = 0; i < node->state.size(); i++)
		{
			for (int j = 0; j < node->state[i].size(); j++)
			{
				hash += std::hash<int>()(node->state[i][j]);
			}
		}

		return static_cast<int>(std::hash<int>()(hash));
	}

	bool operator() (const Node* node1, const Node* node2) const
	{
		return (node1->state == node2->state);
	}
};
