#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


double f(double x)
{
	return (exp(0.7*x) - x*x - 0.5);
}

void bissection(double a, double b, double numite)
{
	double x;

	for (int i = 0; i < numite; ++i)
	{
		x = (a+b)/2;

		cout << "a = " << a << " b = " << b << " x = " << x << "\n";

		if (f(x)*f(a) > 0) // Mesmo sinal
			a = x;
		else
			b = x;
	}

}

int main()
{
	cout.precision(10);
	cout << '\n';

	bissection(-1, 0, 30);

	cout << 0.4691289294;

	cout << "\n\n";
	return 0;
}