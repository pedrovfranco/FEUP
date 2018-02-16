/*
 * Change.cpp
 */

#include "Change.h"

template<class T>
void print_array(const T input[], const int &size)
{
  for (int i = 0; i < size; i++)
  {
    cout << input[i] << ' ';
  }
  cout << "\n\n";
}

void generateSave(int *save, const int &size, const int *coins, const int &numCoins, int currentSum, int currentNumCoins)
{

  for (int i = 0; i < numCoins; i++)
  {
    if (currentSum + coins[i] <= size)
    {
      if (save[currentSum + coins[i]] == -1 || currentNumCoins+1 < save[currentSum + coins[i]])
      {
        save[currentSum + coins[i]] = currentNumCoins+1;
        print_array(save, size);
        generateSave(save, size, coins, numCoins, currentSum + coins[i], currentNumCoins+1);
      }
    }

  }

}

void getMin(int value, int coins[], int numCoins)
{
  int save[value];

  for (int i = 0; i < value; i++)
  {
    save[i] = -1; // MAX
  }

  generateSave(save, value, coins, numCoins, 0, 0);
}

string calcChange(int m, int numCoins, int *coinValues)
{
  int coins[3] = {1,4,5};
  getMin(8, coins, 3);
  return "";
}
