#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define a 20
#define b 0.5

double f(double t, double C, double T)
{
	return (-exp(-b/(T+273))*C);
}

double g(double t, double C, double T)
{
	return (a*exp(-b/(T+273))*C - b*(T-20));
}

void twovarEuler(double h, double C, double T, double tf)
{
	double previousC = C, previousT = T;
	double t = 0;

	while (t <= tf)
	{
		cout << "t = " << t << ", C = " << C << ", T = " << T << "\n";

		C += h*f(t,previousC, previousT);

		T += h*g(t,previousC, previousT);

		previousC = C;
		previousT = T;
		t += h;
	}

}

void twovarRungeKutta(double h, double C, double T, double tf)
{
	double dC1, dC2, dC3, dC4;
	double dT1, dT2, dT3, dT4;
	double t = 0;

	while (t <= tf)
	{
		cout << "t = " << t << ", C = " << C << ", T = " << T << "\n";

		dC1 = h*f(t, C, T);
		dT1 = h*g(t, C, T);

		dC2 = h*f(t + h/2, C + dC1/2, T + dT1/2);
		dT2 = h*g(t + h/2, C + dC1/2, T + dT1/2);

		dC3 = h*f(t + h/2, C + dC2/2, T + dT2/2);
		dT3 = h*g(t + h/2, C + dC2/2, T + dT2/2);

		dC4 = h*f(t + h, C + dC3, T + dT3);
		dT4 = h*g(t + h, C + dC3, T + dT3);
	
		C += (dC1 + 2*dC2 + 2*dC3 + dC4)/6;
		T += (dT1 + 2*dT2 + 2*dT3 + dT4)/6;

		t += h;
	}

}

int main()
{
	cout << '\n';
	double h = 0.25;

	twovarEuler(h, 1, 15, h*2);

	cout << "\n\n";

	twovarEuler(h/2, 1, 15, h*2);

	cout << "\n\n";

	twovarEuler(h/4, 1, 15, h*2);

	cout << "\n\n";
	return 0;
}