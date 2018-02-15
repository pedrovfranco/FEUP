#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


double f(double x, double y)
{
	return (-1/(1 + x*x + y*y));
}

double gradfx(double x, double y)
{
	return (2*x/((1 + x*x + y*y)*(1 + x*x + y*y)));
}

double gradfy(double x, double y)
{
	return (2*y/((1 + x*x + y*y)*(1 + x*x + y*y)));
}

void gradient(double x1, double y1, double h, double numite)
{
	double x2 = x1, y2 = y1;

	for (int i = 0; i < numite; ++i)
	{
		x1 = x2;
		y1 = y2;

		cout << "x = " << x2 << " y = " << y2 << " f = " << f(x2,y2) <<"\n";

		x2 -= h*gradfx(x1,y1);
		y2 -= h*gradfy(x1,y1);

	}
	

}

int main()
{
	cout << '\n';

	gradient(-1, 1, 0.1, 50);

	cout << "\n\n";
	return 0;
}