#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

double g(double x, double y) {
	return (x*y);
}

double power(double x, int expo)
{
	if (expo == 0)
		return 1;

	double temp = x;
	for (unsigned int i = 0; i < expo - 1; i++) {
		temp *= x;
	}
	return temp;
}

double roundDouble(double x, unsigned int precision)
{
	return ((double)round(x * power(10, precision))/ power(10, precision));
}


vector<double> getList(unsigned int expo, double a, double b, unsigned int numSteps) {
	vector<double> res;

	for (unsigned int i = 0; i <= numSteps; i++)
		res.push_back(power(a + (double)i*(b-a)/(double)numSteps, expo));

	return res;
}

vector<double> getDoubleIntegralList(double (*f)(double x, double y), double a, double b, double numSteps) {
	vector<double> res;
	res.resize(numSteps + 1);

	if (a > b)
		swap(a,b);

	for (unsigned int i = 0; i <= numSteps; ++i)
	{
	
		res[i - a] = f(i, i - a);
	}

	return res;
}

double simpson(double h, vector<double> input) {

	double sum = 0;

	for (unsigned int i = 1; i < input.size() - 1; i+=2)
		sum += input[i];
	sum *= 2;

	for (unsigned int i = 2; i < input.size() - 1; i+=2)
		sum += input[i];
	sum *= 2;

	sum += input.front() + input.back();

	return sum*(double)h/3;
}



double doubleIntegral(double hx, double hy, double a, double b, double (*f)(double x, double y)) {
	//TO DO
	// vector<double> sum(input.size(), 0);

	// for (int i = a; i <= b; ++i)
	// {
	// 	sum[i] += simpson(hx, getList(input));

	// }

	// return simpson(h, sum);
}



template<class T>
void print_matrix(const vector<T> &input) {

	for (int i = 0; i < input.size(); ++i)
	{
		cout << input[i] << ' ';
	}
}

template<class T>
void print_matrix(const vector<vector<T> > &input) {

	for (int i = 0; i < input.size(); ++i)
	{
		for (int j = 0; j < input[i].size(); ++j)
		{
			cout << input[i][j] << ' ';
		}
		cout << '\n';
	}
}


int main()
{
	cout << "\n";

	

	cout << "\n\n";
	return 0;
}