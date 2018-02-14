#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define Ta 37

double f(double x)
{
	return (x*x*x -10*sin(x) + 2.8);
}

void bissecao(double a, double b, double numite)
{
	double m;
	for (int i = 0; i < numite; ++i)
	{
		m = (a+b)/2;

		cout << "a = " << a << " b = " << b  << "\n";

		if (f(a)*f(m) > 0)
			a = m;
		else
			b = m;
	}

}

int main()
{
	cout << '\n';

	bissecao(1.5, 4.2, 3);

	cout << "\n\n";
	return 0;
}