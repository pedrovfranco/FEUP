#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template<class T>
T meuabs(T input) {
	if (input < 0)
		return -input;
	else
		return input;
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


vector<double> Gauss_Seidel(const vector<vector<double> > & matrix, vector<double> & guess, const double & precision) {
	
	vector<double> residuo;
	bool flag;

	while (1)
	{
		residuo = verify_matrix_solution(matrix, guess);
		flag = 1;

		for (int j = 0; j < guess.size(); ++j) //Teste de residuo
		{
			if (meuabs(residuo[j]) > precision)
				{
					flag = 0;
					break;
				}
		}

		if (flag)
			return guess;

		
		guess[0] = (101 -(3*guess[1] + 1*guess[2] * 2*guess[3]))/95;
		
		guess[1] = (119 -(4*guess[0] + 10*guess[2] + 5*guess[3]))/100;

		guess[2] = (72 - (3*guess[0] + 9*guess[1] + 5*guess[3]))/55;

		guess[3] = (96 - (10*guess[0] + 2*guess[1] + 4*guess[2]))/80;
	}


}


int main()
{
	cout << "\n";

	vector<vector<double> > input = parser("inputfile");
	vector<double> guess = {1,2,3,4};

	print_matrix(Gauss_Seidel(input, guess, 0.005));

	cout << "\n\n";
	return 0;
}