// Exame2010.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;


//EX1
double fun1(double x) {
	return 2 * log(2 * x);
}

void ex1() {
	double x = 0.9;
	for (unsigned int i = 0; i < 2; i++) {
		cout << "x = " << x << endl;
		x = fun1(x);
	}
}

//EX3

double fun2(double t, double x) {
	return sin(1.0*x) + sin(2.0*t);
}

void ex3() {
	double h = 0.125;
	double t = 1.0, x = 0.0;
	double t1, t2, t3, t4;

	for (unsigned int i = 0; i < 5; i++) {
		cout << "t = " << t << "\t\t x = " << x << endl;

		t1 = h*fun2(t, x);
		t2 = h*fun2(t + h / 2.0, x + t1 / 2.0);
		t3 = h*fun2(t + h / 2.0, x + t2 / 2.0);
		t4 = h*fun2(t + h, x + t3);

		x += t1 / 6.0 + t2 / 3.0 + t3 / 3.0 + t4 / 6.0;
		t += h;

	}
}

//EX5

double fun3(double x, double y) {
	return 6.0 * x*x - x*y + 12.0 * y + y*y - 8.0 * x;
}

double fun3dx(double x, double y) {
	return -y + 12.0 * x - 8.0;
}

double fun3dy(double x, double y) {
	return 2.0 * y - x + 12.0;
}

void ex5() {
	double h = 0.25;
	double x = 0.0, y = 0.0;
	double oldx, oldy;
	for (unsigned int i = 0; i < 2; i++) {
		cout << "X = " << x << "\tY = " << y << "\tZ(Xn) = " << fun3(x, y) << "\tGradiente x = " << fun3dx(x, y) << "\tGradiente y = " << fun3dy(x, y) << "\t\tLambda = " << h << endl;
		oldx = x;
		oldy = y;

		x = x - h*fun3dx(x, y);
		y = y - h*fun3dy(oldx, y);

		if (fun3(x, y) < fun3(oldx, oldy)) {
			h = 2.0 * h;
		}
		else {
			h = h / 2.0;
		}
	}
}



int main()
{
	cout << fixed;
	cout.precision(6);

	//ex1();
	//ex3();
	//ex5();


    return 0;
}

