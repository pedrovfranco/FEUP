#include "node.h"

#include <cmath>
#include <sstream>


Node::Node()
{

}


Node::Node(const Node& node)
{
	this->state = node.state;

	this->coords = node.coords;

	this->cost = node.cost;
	this->h = node.h;

	this->parent = node.parent;
	this->operationName = node.operationName;
}

void Node::setH(int heuristic)
{
	this->h = 0;

	for (int i = 0; i < state.size(); ++i)
	{
		for (int j = 0; j < state[i].size(); ++j)
		{
			std::vector<int> distance = getDistance(j, i);

			if (heuristic == 0)
			{
				if (i != distance[1] || j != distance[0])
					this->h++;
			}
			else if (heuristic == 1)
			{

				this->h += distance[0] + distance[1];
			}
		}
	}

	this->f = this->cost + this->h;
}

bool Node::finished() const
{
	for (int i = 0; i < state.size(); ++i)
	{
		for (int j = 0; j < state[i].size(); ++j)
		{
			std::vector<int> distance = getDistance(j, i);

			if (i != distance[1] || j != distance[0])
				return false;
		}
	}

	return true;
}


std::vector<int> Node::getDistance(int x, int y) const
{
	int value = state[y][x]-1;

	int correctX, correctY;
	if (value != -1)
	{
		correctX = value % state.size();
		correctY = value / state.size();
	}
	else
	{
		correctX = state.size()-1;
		correctY = state.size()-1;
	}

	return {correctX, correctY}; 
}


bool Node::operator==(const Node* node) const
{
	return (this->state == node->state);
}

bool Node::operator==(const Node& node) const
{
	return (this->state == node.state);
}


std::ostream& operator<<(std::ostream& os, const Node& node)
{
	return (os << "Node {state=\n" << printState(node.state) << "cost = " << node.cost << "\n" << "h = "  << node.h << "\n");
}


std::string printState(std::vector<std::vector<int>> state)
{
	std::stringstream ss;
	for (int i = 0; i < state.size(); ++i)
	{
		for (int j = 0; j < state.size(); ++j)
		{
			ss << state[i][j] << " ";
		}

		ss << "\n";
	}

	return ss.str();
}

int hashNode::operator() (const Node* node) const
{
	int hash = 0;

	for (int i = 0; i < node->state.size(); ++i)
	{
		for (int j = 0; j < node->state.size(); ++j)
		{
			hash = node->state.size()*hash + node->state[i][j];
		}
	}

	return static_cast<int>(std::hash<int>()(hash));
}

bool hashNode::operator() (const Node* node1, const Node* node2) const
{
	return (node1->state == node2->state);
}

bool sortH::operator() (const Node* node1, const Node* node2) const
{
	if (node1->h == node2->h)
	{
		for (int i = 0; i < node1->state.size(); ++i)
		{
			for (int j = 0; j < node1->state.size(); ++j)
			{
				if (node1->state[i][j] != node2->state[i][j])
					return (node1->state[i][j] > node2->state[i][j]);
			}
		}

		return false;
	}
	else
	{
		return (node1->h > node2->h);
	}
}

bool sortF::operator() (const Node* node1, const Node* node2) const
{
	return (node1->f < node2->f);
}