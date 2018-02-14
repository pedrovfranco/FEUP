#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define k 2.5

double f(double x)
{
	return (exp(k*x));
}

double diff_f(double x)
{
	return (k*exp(k*x));
}

double L(double x)
{
	return (sqrt(1 + diff_f(x)*diff_f(x)));
}

vector<double> getList(double (*func)(double), double a, double b, double h)
{
	vector<double> res;

	for (double i = a; i <= b; i+=h)
	{
		res.push_back(func(i));
	}

	return res;
} 

double trapezio(vector<double> input, double h)
{
	double sum = 0;

	for (int i = 1; i < input.size() - 1; i++)
	{
		sum += input[i];
	}
	sum *= 2;

	sum += input[0] + input.back();

	return sum*h/2;
}

double simpson(vector<double> input, double h)
{
	double sum = 0;

	for (int i = 1; i < input.size() - 1; i+=2)
	{
		sum += input[i];
	}
	sum *= 2;

	for (int i = 2; i < input.size() - 1; i+=2)
	{
		sum += input[i];
	}
	sum *= 2;

	sum += input[0] + input.back();

	return sum*h/3;
}

int main()
{
	cout.precision(8);
	cout << '\n';

	double h = 0.125;

	vector<double> trap, simp;

	for (int i = 1; i <= 4; i*=2)
	{
		trap.push_back(trapezio(getList(L, 0, 1, h/i), h/i));
		simp.push_back(simpson(getList(L, 0, 1, h/i), h/i));
	}

	for (int i = 0; i < trap.size(); ++i)
	{
		cout << trap[i] << " " << simp[i] << "\n";
	}

	cout << "\n" << (trap[1] - trap[0])/(trap[2] - trap[1]);
	cout << " " << (simp[1] - simp[0])/(simp[2] - simp[1]);

	cout << "\n\n" << abs(trap[2] - trap[1])/3;
	cout << " " << abs(simp[2] - simp[1])/15;
	


	cout << "\n\n";
	return 0;
}