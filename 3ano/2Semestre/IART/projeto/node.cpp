#include "node.h"

using namespace std;


Node::Node()
{

}


Node::Node(const Node& node)
{
	this->state = node.state;

	this->cost = node.cost;
	this->level = node.level;
	this->h = node.h;

	this->parent = node.parent;
	this->operationName = node.operationName;
}

void Node::setH(vector<int> objective)
{
	this->h = abs(this->state[0] - objective[0]) + abs(this->state[1] - objective[1]);

	this->f = this->cost + this->h;
}


bool Node::operator==(const Node* node) const
{
	return (this->state == node->state);
}

bool Node::operator==(const Node& node) const
{
	return (this->state == node.state);
}

// bool Node::operator>(const Node* node) const
// {
// 	return (this->h < node->h);
// }

// bool Node::operator>(const Node& node) const
// {
// 	return (this->h < node.h);
// }


ostream& operator<<(ostream& os, const Node& node)
{
	return (os << "Node {state=\n" << printState(node.state) << "cost = " << node.cost << "\n" << "h = "  << node.h << "\n");
}


string printState(vector<int> state)
{
	string foo = "";

	foo += "[";
	for (int i = 0; i < state.size(); ++i)
	{
		foo += to_string(state[i]);

		if (i != state.size()-1)
			foo += ", ";

	}

	foo += "],\n";

	return foo;
}

int hashNode::operator() (const Node* node) const
{
	return static_cast<int>(std::hash<int>()(node->state[0]) + std::hash<int>()(node->state[1]));
}

bool hashNode::operator() (const Node* node1, const Node* node2) const
{
	return (node1->state == node2->state);
}


bool sortH::operator() (const Node* node1, const Node* node2) const
{
	for (int i = 0; i < node1->state.size(); i++)
	{
		if (node1->state[i] != node2->state[i])
			return (node1->state[i] < node2->state[i]);
	}

	return false;
}

