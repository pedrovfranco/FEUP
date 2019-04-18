#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

#include "node.h"
#include "ui_utilities.h"
#include "macros.h"

using namespace std;


int algorithm_menu();

void agent(string map);

void menu();

void printPath(Node* node);

void printMap(Node* node);

void printPath2(Node* node);


#endif