
#include "node.h"

using namespace std;


Node::Node()
{

}

Node::Node(int n)
{
	this->cost = 0;

	unordered_set<int> set;
	int randNum;
	
	vector<int> foobar(n, 0);
	this->state = vector<vector<int>>(n, foobar);

	// for (int i = 0; i < n; i++)
	// {
	// 	state.push_back(vector<int>());

	// 	for (int j = 0; j < n; j++)
	// 	{
	// 		randNum = rand()%(n*n);
	// 		while (!set.insert(randNum).second)
	// 		{
	// 			randNum = rand()%(n*n)+1;
	// 		}
			
	// 		state[i].push_back(randNum);		
	// 	}
	// }
	
	if (n == 4)
	{
		this->state[0] = {2,3,7,4};
		this->state[1] = {0,6,5,8};
		this->state[2] = {1,10,15,11};
		this->state[3] = {9,13,14,12};

		this->x = 0;
		this->y = 1;
	}
	else if (n == 3)
	{
		this->state[0] = {1,2,3};
		this->state[1] = {4,8,0};
		this->state[2] = {7,6,5};

		this->x = 2;
		this->y = 1;
	}
	
}

Node::Node(const Node& node)
{
	this->state = node.state;

	this->x = node.x;
	this->y = node.y;

	this->cost = node.cost;
	this->level = node.level;
	this->h = node.h;

	this->parent = node.parent;
	this->operationName = node.operationName;
}

void Node::setH(vector<vector<int>> objective)
{
	// this->h = (this->state.size()*this->state.size());

	this->h = 0;

	for (int i = 0; i < this->state.size(); ++i)
	{
		for (int j = 0; j < this->state[i].size(); ++j)
		{
			// if (this->state[i][j] == objective[i][j])
			// {
			// 	this->h--;
			// }

			int x,y;
			if (this->state[i][j] == 0)
			{
				x = this->state.size()-1;
				y = this->state.size()-1;
			}
			else
			{
				x = (this->state[i][j]-1)%3;
				y = (this->state[i][j]-1)/3;
			}
			
			this->h += abs(x-j) + abs(y-i);
		}
	}

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
	os << "Node {state=\n";
	for (int i = 0; i < node.state.size(); ++i)
	{
		os << "[";
		for (int j = 0; j < node.state[i].size(); ++j)
		{
			os << node.state[i][j];

			if (j != node.state[i].size()-1)
				os << ", ";
		}
		os << "],\n";
	}

	return (os << "cost = " << node.cost << "\n" << "h = "  << node.h << "\n");
}


string printState(vector<vector<int>> state)
{
	string foo = "";

	for (int i = 0; i < state.size(); ++i)
	{
		foo += "[";
		for (int j = 0; j < state[i].size(); ++j)
		{
			foo += to_string(state[i][j]);

			if (j != state[i].size()-1)
				foo += ", ";
		}
		foo += "],\n";
	}

	return foo;
}

int hashNode::operator() (const Node* node) const
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

bool hashNode::operator() (const Node* node1, const Node* node2) const
{
	return (node1->state == node2->state);
}


bool sortH::operator() (const Node* node1, const Node* node2) const
{
	if (node1->f == node2->f)
	{
		for (int i = 0; i < node1->state.size(); ++i)
		{
			for (int j = 0; j < node1->state.size(); ++j)
			{
				if (node1->state[i][j] != node2->state[i][j])
					return (node1->state[i][j] < node2->state[i][j]);
			}
		}

		return false;
	}
	else
		return(node1->f < node2->f);
}

