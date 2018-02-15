#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


double simpson(vector<double> input, double h)
{
	double sum = 0;

	for (int i = 1; i < input.size() - 1; i+=2)
	{
		sum += input[i];
	}
	sum *= 2;

	for (int i = 2; i < input.size() - 1; i+=2)
	{
		sum += input[i];
	}
	sum *= 2;

	sum += input[0] + input.back();
	sum = sum * h / 3;

	return sum;
}


int main()
{
	cout << '\n';

	vector<double> input = {0.18, 0.91, 0.83, 1.23, 0.88, 1.37, 0.8, 1.34, 0.43};
	vector<double> input2 = {0.18, 0.83, 0.88, 0.8, 0.43};
	vector<double> input3 = {0.18, 0.88, 0.43};

	cout << "Valor do integral: " << simpson(input, 0.2);
	// cout << "\nErro estimado :" << (simpson(input2, 0.4) - simpson(input3, 0.8))/(simpson(input, 0.2) - simpson(input2, 0.4));
	cout << "\nErro estimado :" << (simpson(input, 0.2) - simpson(input2, 0.4))/15;


	cout << "\n\n";
	return 0;
}