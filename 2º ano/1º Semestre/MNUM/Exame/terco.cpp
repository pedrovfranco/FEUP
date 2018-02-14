#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define B (sqrt(5) - 1)/2
#define A B*B

double f(double x)
{
	return (x*x);
}

void aurea(double x1, double x2, double numite) // For comparison with the other method
{
	double x3 = A*(x2-x1) + x1, x4 = B*(x2-x1) + x1;

	for (int i = 0; i < numite; ++i)
	{
		x3 = A*(x2-x1) + x1;
		x4 = B*(x2-x1) + x1;

		cout << "x1 = " << x1 << " x2 = " << x2 << " x3 = " << x3 << " x4 = " << x4 << "\n";

		if (f(x3) < f(x4))
		{
			x2 = x4;
			x4 = x3;
			x3 = B*(x4-x1) + x1;
		}
		else
		{
			x1 = x3;
			x3 = x4;
			x4 = B*(x2-x3) + x3;
		}

	}

}


void terco(double x1, double x2, double numite)
{
	double x3, x4;

	for (int i = 0; i < numite; ++i)
	{
		x3 = (x2 - x1)/3 + x1;
		x4 = x2 - (x2 - x1)/3;

		cout << "x1 = " << x1 << " x2 = " << x2 << " x3 = " << x3 << " x4 = " << x4 << "\n";

		if (f(x3) > f(x4))
		{
			x1 = x3;
		}
		else
		{
			x2 = x4;
		}

	}

}



int main()
{
	cout << '\n';

	terco(-8,10,15);

	cout << "\n\n";
	return 0;
}