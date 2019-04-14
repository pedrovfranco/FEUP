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

	cout << "\n\n";
}


void gauss(vector<vector<double> > matrix)
{
	double temp;

	print_matrix(matrix);

	for (int i = 0; i < matrix.size(); ++i)
	{

		for (int j = i+1; j < matrix.size(); ++j)
		{
			temp = matrix[j][i] / matrix[i][i];
			for (int k = 0; k < matrix[i].size(); ++k)
			{
				matrix[j][k] -= matrix[i][k]*temp;
			}

		}

	}

	print_matrix(matrix);

	for (int i = 0; i < matrix.size(); ++i)
	{
		temp = matrix[i][i];
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			matrix[i][j] /= temp;
		}
	}

	print_matrix(matrix);

	for (int i = matrix.size() - 1; i >= 0; --i)
	{

		for (int j = matrix[i].size() - 2; j > i; --j)
		{
			matrix[i].back() -= matrix[i][j]*matrix[j].back();

			print_matrix(matrix);
		}
	}

	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size() - 1; ++j)
		{
			if (i != j)
				matrix[i][j] = 0;
		}
	}

	print_matrix(matrix);

}



int main()
{
	cout << '\n';

	vector<vector<double> > input = {{1,(double)1/2,(double)1/3, -1}, {(double)1/2, (double)1/3,(double)1/4,1}, {(double)1/3, (double)1/4, (double)1/5, 1}};

	gauss(input);

	cout << "\n\n";
	return 0;
}