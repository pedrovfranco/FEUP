#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define Ta 42

double f(double t, double T)
{
	return (-0.25*(T-Ta));
}

void euler(double h, double t, double T)
{

	for (int i = 0; i < 3; ++i)
	{
		cout << "t = " << t << " T = " << T << "\n";

		T += h*f(t, T);

		t += h;
	}

}


int main()
{
	cout << '\n';

	euler(0.4, 5, 10);

	cout << "\n\n";
	return 0;
}