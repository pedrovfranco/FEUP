#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>

#include "node.h"

typedef Node* (*Operator)(Node*);

extern std::vector<Operator> operations;
extern std::vector<std::string> operationNames;

void initiateOperators();

Node* initiateMap(std::string filename);

void loadMap(std::string filename, std::vector<std::vector<int>>& map, std::vector<int>& coords);

void initiateOperators();


#endif