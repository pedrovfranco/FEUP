#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double power(double x, int expo)
{
  if (expo == 0)
    return 1;

  double temp = x;
  for (unsigned int i = 0; i < expo - 1; i++) {
    temp *= x;
  }
  return temp;
}

double roundDouble(double x, unsigned int precision)
{
  return ((double)round(x * power(10, precision))/ power(10, precision));
}

vector<double> getList(unsigned int expo, double a, double b, unsigned int numSteps) {
  vector<double> res;

  for (unsigned int i = 0; i <= numSteps; i++)
    res.push_back(power(a + (double)i*(b-a)/(double)numSteps, expo));

  return res;
}


double trapezio(double h, vector<double> input) {

  double sum = 0;

  for (unsigned int i = 1; i < input.size() - 1; i++)
    sum += input[i];

  sum *= 2;
  sum += input.front() + input.back();

  return sum*h/2;
}

double simpson(double h, vector<double> input) {

  double sum = 0;

  for (unsigned int i = 1; i < input.size() - 1; i+=2)
    sum += input[i];
  sum *= 2;

  for (unsigned int i = 2; i < input.size() - 1; i+=2)
    sum += input[i];
  sum *= 2;

  sum += input.front() + input.back();

  return sum*(double)h/3;
}


template<class T>
void print_matrix(vector<T> matrix) {
  for (unsigned int i = 0; i < matrix.size(); i++)
  {
    for (unsigned int j = 0; j < matrix[i].size(); j++)
    {
        cout << matrix[i][j] << " ";
    }
    cout << '\n';
  }
}


int main()
{
  cout.precision(10);
  cout << '\n';

  // unsigned int numSteps = 8;
  // unsigned int expo = 1;
  //
  // cout << trapezio((double)1/numSteps, getList(expo, 0, 1, numSteps));

  // vector<vector<double> > matrix;
  //
  // for (unsigned int i = 1; i <= 8; i++)
  // {
  //   matrix.push_back({});
  //
  //   for (unsigned int j = 2; j <= 64; j*= 2)
  //     matrix[i - 1].push_back(roundDouble(abs(trapezio((double)1/10000, getList(i, 0, 1, 10000)) - trapezio((double)1/j, getList(i, 0, 1, j))), 4));
  // }
  // print_matrix(matrix);

  for (int i = 1; i < 8; i++) {
    cout << simpson((double)1/8, getList(i, 0, 1, 8)) << " ";
  }


  cout << "\n\n";
  return 0;
}
