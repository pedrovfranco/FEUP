#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Node
{
public:
	vector<int> state = {0, 0};
	int cost;
	int level;
	Node* parent = NULL;
	string operationName = "";

	Node()
	{
		this->cost = 0;
	}

	Node(int state1, int state2, int cost)
	{
		this->state[0] = state1;
		this->state[1] = state2;

		this->cost = cost;
	}

	Node(const Node& node)
	{
		this->state[0] = node.state[0];
		this->state[1] = node.state[1];

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

inline ostream& operator<<(ostream& os, const Node& node)
{
	return (os << "Node {state=[" << node.state[0] << ", " << node.state[1] << "], " << "cost = " << node.cost);
}

struct hashNode
{
	int operator() (const Node* node) const
	{
		return static_cast<int>(std::hash<int>()(node->state[0]) + std::hash<int>()(node->state[1]));
	}

	bool operator() (const Node* node1, const Node* node2) const
	{
		return (node1->state == node2->state);
	}
};
