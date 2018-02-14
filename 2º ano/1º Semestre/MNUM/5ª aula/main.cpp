#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void print_matrix(const vector<vector<double> > &matrix) {
	
	for(int i = 0 ; i < matrix.size(); i++)
	{
		cout << "\n";
		for(int j = 0 ; j < matrix[i].size(); j++)
			cout << matrix[i][j] << " ";
		
	}
	cout << "\n\n";
}

void print_matrix(const vector<double> &matrix) {
	
	for(int i = 0 ; i < matrix.size(); i++)
	{
		cout << matrix[i] << " ";
		
	}
	cout << "\n\n";
}

vector<double> solve_linear(vector<vector<double> > matrix) {
	double temp;
	
	for(int i = 0; i < matrix.size() - 1; i++)
	{
		for(int j = i + 1; j < matrix.size(); j++)
		{
			temp = matrix[j][i] / matrix[i][i];
			
			for(int k = i; k < matrix[i].size(); k++)
				matrix[j][k] -= matrix[i][k]*temp;
			
		}
		
	}
	
	for(int i = 0; i < matrix.size(); i++)
	{		
		temp = matrix[i][i];
		
		for(int k = 0; k < matrix[i].size(); k++)
			matrix[i][k] /= temp;
		
	}
	
	vector<double> res (matrix.size(), 0.0);
	temp = 0;
	for(int i = matrix.size() - 1; i >= 0; i--)
	{
		temp = matrix[i].back();
		for(int j = i + 1; j < matrix[i].size() - 1; j++)
		{
			temp -= matrix[i][j] * res[j];
		}
		res[i] = temp;
	}
	
	return res;
}


vector<vector<double> > parser(const string & filename) {

	ifstream input(filename);

	vector<vector<double> > res;
	vector<double> row;
	string tempstr;
	double temp;

	while(getline(input, tempstr, '\n'))
	{
		row.resize(0);
		istringstream ss(tempstr);

		while (getline(ss, tempstr, ' '))
		{
			row.push_back(stod(tempstr));


		}
		res.push_back(row);
	}
	return res;
}


int main()
{
	cout << "\n";
	vector<vector<double> > matrix = parser("inputfile");
	
	print_matrix(solve_linear(matrix));
	
	cout << "\n\n";
	return 0;
}