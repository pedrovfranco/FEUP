#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define a 20
#define b 0.5
#define A 0.5

vector<vector<double> > getMatrix(string filename)
{
  vector<vector<double> > res;
  ifstream input(filename);
  if (!input.is_open())
    return {};
  string tempstr;

  while(getline(input, tempstr, '\n'))
  {
    res.push_back({});
    stringstream ss(tempstr);

    while(getline(ss, tempstr, ' '))
    {
      res.back().push_back(stod(tempstr));
    }
  }

  return res;
}

double f(double C, double T) {
	return (-exp((double)-b/(T+273))*C);
}

double g(double C, double T) {
	return (a*exp((double)-b/(T+273))*C - b*(double)(T - 20));
}

double quociente(double s1, double s2, double s3) {
	return (s2 - s1)/(s3 - s2);
}

double quociente(vector<double> S) {
	return (S[S.size() - 2] - S[S.size() - 3])/(S[S.size() - 1] - S[S.size() - 2]);
}

template<class T>
void print_matrix(vector<T> input)
{
  cout << '\n';
  for (int i = 0; i < input.size(); i++)
      cout << input[i] << ' ';

}

template<class T>
void print_matrix(vector<vector<T> > input)
{
  cout << '\n';
  for (int i = 0; i < input.size(); i++)
  {
    for (int j = 0; j < input[i].size(); j++)
      cout << input[i][j] << ' ';

    cout << '\n';
  }

}



void euler(double x, double xf, double y, double h)
{
	while(x <= xf)
	{
		cout << "x = " << x << " y = " << y << '\n';

		y += h*f(x,y);
		x += h;
	}

}

void RK(double x, double xf, double y, double h)
{
	double d1;
	double d2;
	double d3;
	double d4;

	while(x <= xf)
	{
		cout << "x = " << x << " y = " << y << '\n';

		d1 = h*f(x, y);
		d2 = h*f(x + h/2, y + d1/2);
		d3 = h*f(x + h/2, y + d2/2);
		d4 = h*f(x + h, y + d3);

		y += d1/6 + d2/3 + d3/3 + d4/6;
		x += h;
	}

}

void euler_sistema(double tf, double C, double T, double h)
{
	double t = 0;
	double Cprevious;
	double Tprevious;

	vector<double> S;

	while(t <= tf)
	{
		cout << "t = " << t << " C = " << C << " T = " << T << '\n';

		Cprevious = C;
		Tprevious = T;

		C += h*f(Cprevious,Tprevious);
		T += h*g(Cprevious,Tprevious);
		t += h;
	}

}

void RK_sistema(double tf, double C, double T, double h)
{
	double dC1;
	double dC2;
	double dC3;
	double dC4;

	double dT1;
	double dT2;
	double dT3;
	double dT4;

	double t = 0;

	while(t <= tf)
	{
		cout << "t = " << t << " C = " << C << " T = " << T << '\n';

		dC1 = h*f(C, T);
		dT1 = h*g(C, T);

		dC2 = h*f(C + dC1/2, T + dT1/2);
		dT2 = h*g(C + dC1/2, T + dT1/2);

		dC3 = h*f(C + dC2/2, T + dT2/2);
		dT3 = h*g(C + dC2/2, T + dT2/2);

		dC4 = h*f(C + dC3, T + dT3);
		dT4 = h*g(C + dC3, T + dT3);

		C += dC1/6 + dC2/3 + dC3/3 + dC4/6;
		T += dT1/6 + dT2/3 + dT3/3 + dT4/6;

		t += h;
	}

}

double simpson(vector<double> input, double h) {
  double sum = 0;

  for (unsigned int i = 1; i < input.size() - 1; i+=2)
    sum += input[i];
  sum *= 2;

  for (unsigned int i = 2; i < input.size() - 1; i+=2)
    sum += input[i];
  sum *= 2;

  sum += input.front() + input.back();

  return h*sum/3;
}

vector<double> gauss_seidel(vector<vector<double> > input, vector<double> guess, unsigned int numSteps) {

  for (int i = 0; i < numSteps; i++)
  {
    for (int j = 0; j < input.size(); j++)
    {
      guess[j] = input[j].back();
      for (int k = 0; k < (input[j].size() - 1); k++)
      {
        if (k != j)
          guess[j] -= guess[k]*input[j][k];
      }
      guess[j] /= input[j][j];
    }
    print_matrix(guess);
  }

  return guess;
}

double func(double t, double y, double dy) {
  return (A + t*t + t*dy);
}

void euler_segunda(double tf, double y, double dy, double h)
{
  double t = 0;
  double previousdy;

  while(t <= tf)
  {
    cout << "t = " << t << " y = " << y << " y\' = " << dy << '\n';

    previousdy = dy;

    y += h*dy;
    dy += h*func(t,y,dy);
    t += h;

  }

}

void RK_segunda(double tf, double y, double dy, double h)
{
  double t = 0;
  double previousdy;
  vector<double> Dy(4,0);
  vector<double> Ddy(4,0);

  while(t <= tf)
  {
    cout << "t = " << t << " y = " << y << " y\' = " << dy << '\n';

    previousdy = dy;

    Dy[0] = h*dy;
    Ddy[0] = h*func(t,y,dy);

    Dy[1] = h*dy;
    Ddy[1] = h*func(t, y + Dy[0]/2, dy + Ddy[0]/2);

    Dy[2] = h*dy;
    Ddy[2] = h*func(t, y + Dy[1]/2, dy + Ddy[1]/2);

    Dy[3] = h*dy;
    Ddy[3] = h*func(t, y + Dy[2], dy + Ddy[2]);

    y += Dy[0]/6 + Dy[1]/3 + Dy[2]/3 + Dy[3]/6;
    dy += Ddy[0]/6 + Ddy[1]/3 + Ddy[2]/3 + Ddy[3]/6;

    t += h;

  }

}

int main()
{
	cout << '\n';

  RK_segunda(0.5, 0, 1, 0.25);

	cout << "\n\n";
	return 0;
}
