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
		for (int j = 0; j < i; ++j)
		{
			matrix[i][j] = 0;
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
			matrix[i][j] = 0;
		}
	}

	print_matrix(matrix);

}

void gauss_seidel(vector<vector<double> > input, vector<double> guess)
{
	double temp;

	for (int k = 0; k < 5000; ++k)
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

vector<double> get_residue(vector<vector<double> > matrix, vector<double> vars)
{
	vector<double> res;
	res.resize(matrix.size());

	for (int i = 0; i < matrix.size(); ++i)
	{
		res[i] = matrix[i].back();

		for (int j = 0; j < matrix[i].size() - 1; ++j)
		{
			res[i] -= matrix[i][j]*vars[j];
		}
	}

	return res;
}


int main()
{
	cout << '\n';

	vector<vector<double> > input = {{0.5,0.33333,0.25,0.2,0}, {0.33333,0.25,0.2,0.16667,0.1}, {0.25,0.2,0.16667,0.14286,0.2}, {0.2,0.16667,0.14286,0.125,0}};
	vector<double> vars = {308.31575, -2268.24132, 4466.38001, -2573.4};

	print_matrix(get_residue(input, vars));

	cout << "\n\n";
	return 0;
}