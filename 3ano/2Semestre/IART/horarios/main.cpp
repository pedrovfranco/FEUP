#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <queue>
#include <functional>
#include <time.h> 
#include <algorithm>

#include "node.h"
#include "mapLoader.h"

#define DEBUG 0

using namespace std;


vector<int> intersect(vector<int> a, vector<int> b)
{
	vector<int> res;
	bool flag;
	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = 0; j < b.size(); ++j)
		{
			if (a[i] == b[j])
			{
				flag = true;
				for (int k = 0; k < res.size(); ++k)
				{
					if (res[k] == a[i])
					{
						flag = false;
						break;
					}
				}

				if (flag)
					res.push_back(a[i]);
			}
		}
	}

	return res;
}

vector<vector<int>> conflictsTable(vector<vector<int>> input)
{
	vector<vector<int>> result;

	for (int i = 0; i < input.size(); ++i)
	{
		for (int j = i+1; j < input.size(); ++j) // Combinations 2by2
		{
			result.push_back(intersect(input[i], input[j]));
		}
	}

	return result;
}




int main()
{
	int numSlots, numClasses;
	vector<vector<int>> initial = loadMap("input.txt", numSlots, numClasses);
	vector<vector<int>> table;

	clock_t time = clock();

	table = conflictsTable(initial);

	for (int i = 0; i < table.size(); ++i)
	{
		for (int j = 0; j < table[i].size(); ++j)
		{
			cout << table[i][j] << " ";
		}

		cout << "\n";
	}

	double deltaTime = (double)(clock()-time)/CLOCKS_PER_SEC;

	printf("\nFinished in %f seconds.\n", deltaTime);

	return 0;
}