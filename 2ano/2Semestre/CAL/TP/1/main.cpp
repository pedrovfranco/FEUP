#include <iostream>
#include <vector>

using namespace std;

void troco(vector<int>& minimo, int restante, vector<int> curr, const vector<int> &moedas)
{
	if (restante == 0 && curr.size() < minimo.size())
		minimo = curr;


	for (int i = moedas.size()-1; i >= 0; --i)
	{
		if (moedas[i] <= restante)
		{
			curr.push_back(moedas[i]);

			troco(minimo, restante-moedas[i], curr, moedas);

			curr.erase(curr.end()-1);
		}
	}

}


int troco(int valor, vector<int> moedas)
{
	vector<int> min;
	min.resize(100);
	vector<int> curr;

	troco(min, valor, curr, moedas);

	return min.size();
}


int main()
{
	cout << "\n";

	cout << troco(8, {1,4,5});

	cout << "\n\n";
	return 0;
}