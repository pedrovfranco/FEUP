#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define Ta 37

double f(double T)
{
	return (-0.25*(T-Ta));
}

void euler(double h, double t, double T)
{

	for (int i = 0; i < 3; ++i)
	{
		cout << "t = " << t << " T = " << T << "\n";

		T += h*f(T);
		t += h;
	}

}

int main()
{
	cout << '\n';

	euler(0.4, 5, 3);

	cout << "\n\n";
	return 0;
}