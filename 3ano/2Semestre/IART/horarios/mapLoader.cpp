#include "mapLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>


vector<vector<int>> loadMap(string filename, int &slots, int &classes)
{
	ifstream ifs(filename);
	vector<vector<int>> ret;
	string line, cell;
	int cellValue;

	for (int i = 0; getline(ifs, line); i++)
	{
		stringstream ss(line);
		vector<int> row;
		
		if (i == 0)
		{
			getline(ss, cell, ' ');
			slots = stoi(cell);

			getline(ss, cell, ' ');
			classes = stoi(cell);
		}

		for (int j = 0; getline(ss, cell, ' '); ++j)
		{
			if (cell[0] == '/')
			{
				break;
			}

			cellValue = cell[0] - '0';

			row.push_back(cellValue);
		}

		ret.push_back(row);

	}

	return ret;
}
