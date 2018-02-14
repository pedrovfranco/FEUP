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


vector<vector<double> > multiply_matrix(vector<vector<double> > input1, vector<vector<double> > input2)
{
	vector<double> temp(input2[0].size(), 0);
	vector<vector<double> > res (input1.size(), temp);

	for (int i = 0; i < input1.size(); ++i)
	{
		for (int j = 0; j < input2[i].size(); ++j)
		{
			for (int k = 0; k < input1[i].size(); ++k)
			{
				res[i][j] += input1[i][k] * input2[k][j];
			}
		}
	}

	return res;
}

vector<vector<double> > add_matrix(vector<vector<double> > input1, vector<vector<double> > input2)
{

	for (int i = 0; i < input1.size(); ++i)
	{
		for (int j = 0; j < input1[i].size(); ++j)
		{
			input1[i][j] += input2[i][j];
		}
	}

	return input1;
}

vector<vector<double> > subtract_matrix(vector<vector<double> > input1, vector<vector<double> > input2)
{

	for (int i = 0; i < input1.size(); ++i)
	{
		for (int j = 0; j < input1[i].size(); ++j)
		{
			input1[i][j] -= input2[i][j];
		}
	}

	return input1;
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



int main()
{
	cout << '\n';

	double d = 0.05;
	vector<vector<double> > input = {{1,(double)1/2,(double)1/3, -1}, {(double)1/2, (double)1/3, (double)1/4, 1}, {(double)1/3, (double)1/4, (double)1/5, 1}};
	vector<vector<double> > A = {{1,(double)1/2,(double)1/3}, {(double)1/2, (double)1/3, (double)1/4}, {(double)1/3, (double)1/4, (double)1/5}};
	vector<vector<double> > Ainv = {{9, -36, 30}, {-36, 192, -180}, {30, -180, 180}};
	vector<vector<double> > x = {{-15}, {48}, {-30}};

	vector<double> temp(A[0].size() - 1, d);
	vector<vector<double> > dA(A.size(), temp);

	vector<double> temp2(1, d);
	vector<vector<double> > dB(A.size(), temp2);

	vector<vector<double> > dx = {{-0.3}, {2.4}, {-3}};

	vector<vector<double> > temp3 = subtract_matrix(dB, multiply_matrix(dA, x));

	for (int i = 0; i < input.size(); ++i)
	{
		input[i].back() = temp3[i].back();
	}

	// print_matrix(subtract_matrix(multiply_matrix(Ainv, dB), multiply_matrix(Ainv, multiply_matrix(dA, x))));

	// for (int i = 0; i < input.size(); ++i)
	// {
	// 	input[i].back() += d;

	// }

	gauss(input);

	cout << "\n\n";
	return 0;
}