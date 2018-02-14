#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template<class T>
void swap(T a, T b) {
	T foo = a;
	a = b;
	b = foo;
}

vector<vector<double> > multiply_matrix(vector<vector<double> > m1, vector<vector<double> > m2) {
	if (m1[0].size() != m2.size())
		return {{}};

	vector<vector<double> > res (m1.size(), vector<double> (m2[0].size(),0.0));

	double temp = 0;
	for (int i = 0; i < res.size() ;i++) //Iterador de colunas
	{
		for (int j = 0; j < res[i].size() ; j++) //Iterador de linhas
		{
			temp = 0;

			for (int k = 0; k < m2.size(); k++) //Iterador da multiplicacao, itera ao longo de cada coluna de m2 e ao longo de cada linha de m1
			{
				temp += m1[i][k]*m2[k][j];
			}

			res[i][j] = temp;
		}

	}


	return res;

}

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
	if (matrix[0][0] == 0)
		for(int i = 0; i < matrix.size(); i++)
			if (matrix[i][0] != 0)
				swap(matrix[0], matrix[i]);

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


vector<double> verify_matrix_solution(vector<vector<double> > matrix, vector<double> solution) {
	vector<double> res(solution.size(), 0);
	double temp;
	for (int i = 0; i < matrix.size(); i++)
	{
		temp = 0;
		for (int j = 0; j < matrix[i].size() - 1; j++)
		{
			temp += matrix[i][j]*solution[j];

		}
		res[i] = matrix[i].back() - temp;
	}

	return res;
}


int main() {
	cout.precision(10);
	cout << "\n";
	vector<vector<double> > matrix1 = parser("inputfile");

	print_matrix(solve_linear(matrix1));

	cout << "\n\n";
	return 0;
}
