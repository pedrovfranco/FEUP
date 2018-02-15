#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void print_matrix(vector<double> input)
{
	for (int i = 0; i < input.size(); ++i)
	{
		cout << input[i] << " ";
	}
	cout << "\n";
}

void print_matrix(vector<vector<double> > input)
{
	for (int i = 0; i < input.size(); ++i)
	{
		for (int j = 0; j < input[i].size(); ++j)
			cout << input[i][j] << " ";

		cout << "\n";
	}
}

void gauss_seidel(vector<vector<double> > input, vector<double> guess)
{
	double temp;

	for (int k = 0; k < 3; ++k)
	{
		print_matrix(guess);

		for (int i = 0; i < input.size(); ++i)
		{
			guess[i] = input[i].back();

			for (int j = 0; j < input[i].size(); ++j)
			{
				if (i != j)
					guess[i] -= input[i][j]*guess[j];
			}
			guess[i] /= input[i][i];
		}
	}
}


int main()
{
	cout << '\n';

	vector<vector<double> > input = {{6,0.5,3,0.25,2.5}, {1.2,3,0.25,2,3.8}, {-1,0.25,4,2,10}, {2,4,1,8,7}};
	vector<double> guess = {0,0,0,0};

	gauss_seidel(input, guess);

	cout << "\n\n";
	return 0;
}