#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


double f1(double x)
{
	return (sqrt(exp(x))/2);
}

double f2(double x)
{
	return (exp(x)/(4*x));
}

double f3(double x)
{
	return (-sqrt(exp(x))/2);
}

double f4(double x)
{
	return (2*log(2*x));
}

double picard(double (*f)(double), double guess, int numite)
{

	for (int i = 0; i < numite; ++i)
	{
		cout << guess << "\n";
		guess = f(guess);
	}

	return guess;
}

int main()
{
	cout << '\n';

	cout << picard(f4, 1.1, 1);

	cout << "\n\n";
	return 0;
}