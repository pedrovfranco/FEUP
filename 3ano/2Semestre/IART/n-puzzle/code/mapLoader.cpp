#include "mapLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

std::vector<Operator> operations;
std::vector<std::string> operationNames;


Node* initiateMap(std::string filename)
{
	initiateOperators();
	
	std::vector<std::vector<int>> startState;
	std::vector<int> startCoords;

	loadMap(filename, startState, startCoords);
	
	Node* rootNode = new Node();
	rootNode->state = startState;
	rootNode->coords = startCoords;
	rootNode->setH(0);

	return rootNode;
}

void loadMap(std::string filename, std::vector<std::vector<int>>& map, std::vector<int>& coords)
{
	std::ifstream ifs(filename);

	if (ifs.fail())
	{
		std::cerr << "Map not found!";
		exit(1);
	}

	std::string line, cell;
	int cellValue;

	map.resize(0);
	coords.resize(0);

	while (getline(ifs, line))
	{
		if (!(line[0] >= '0' && line[0] <= '9'))
			continue;
	
		if (line.back() != ',')
			line.push_back(',');

		std::stringstream ss(line);
		std::vector<int> row;
		for (int i = 0; getline(ss, cell, ','); ++i)
		{
			cellValue = stoi(cell);

			if (cellValue == 0)
			{
				coords.push_back(row.size());
				coords.push_back(map.size());
			}

			row.push_back(cellValue);
		}

		map.push_back(row);
	}

	ifs.close();
}


void initiateOperators()
{
	Operator up = [](Node* node) { Node* newNode = new Node(*node); if(newNode->coords[1] > 0) { std::swap(newNode->state[newNode->coords[1]][newNode->coords[0]], newNode->state[newNode->coords[1]-1][newNode->coords[0]]); newNode->coords[1]--;} return newNode;};
	Operator right = [](Node* node) { Node* newNode = new Node(*node); if(newNode->coords[0] < newNode->state[0].size()-1) { std::swap(newNode->state[newNode->coords[1]][newNode->coords[0]], newNode->state[newNode->coords[1]][newNode->coords[0]+1]); newNode->coords[0]++;} return newNode;};
	Operator down = [](Node* node) { Node* newNode = new Node(*node); if(newNode->coords[1] < newNode->state.size()-1) { std::swap(newNode->state[newNode->coords[1]][newNode->coords[0]], newNode->state[newNode->coords[1]+1][newNode->coords[0]]); newNode->coords[1]++;} return newNode;};
	Operator left = [](Node* node) { Node* newNode = new Node(*node); if(newNode->coords[0] > 0) { std::swap(newNode->state[newNode->coords[1]][newNode->coords[0]], newNode->state[newNode->coords[1]][newNode->coords[0]-1]); newNode->coords[0]--;} return newNode;};

	operations = {up, right, down, left};
	operationNames = {"up", "right", "down", "left"};
}