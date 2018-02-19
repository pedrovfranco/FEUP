/*
 * Change.cpp
 */

#include "Change.h"
#include <string>

template<class T>
void print_array(const T input[], const int &size)
{
  for (int i = 0; i < size; i++)
  {
    cout << input[i] << ' ';
  }
  cout << "\n\n";
}

void generateSave(int &min, string currPath, string &minPath, const int &max, const int *coins, const int &numCoins, int currentSum, int currentNumCoins)
{

  for (int i = 0; i < numCoins; i++)
  {
    if (currentSum + coins[i] == max && currentNumCoins+1 < min)
    {
      min = currentNumCoins+1;
      minPath = currPath+(char)(coins[i]+'0')+";";
    }

    if (currentSum + coins[i] <= max)
      generateSave(min, (currPath + to_string(coins[i]) + ";"), minPath, max, coins, numCoins, currentSum + coins[i], currentNumCoins+1);
  }

}

string calcChange(int m, int numCoins, int *coinValues)
{
  if (m == 0)
    return "";
  
  if (coinValues[0] > m)
    return "-";

  int min = 999;
  string minPath;

  generateSave(min, "", minPath, m, coinValues, numCoins, 0, 0);

  for (int i = 0; i < minPath.length()/2; ++i)
  {
    swap(minPath[i], minPath[minPath.length() - i - 2]);
  }

  return minPath;
}
