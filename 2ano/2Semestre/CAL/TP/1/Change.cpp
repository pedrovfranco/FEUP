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

void print_vector(const vector<int> &input)
{
   for (int i = 0; i < input.size(); i++)
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

void getTroco(vector<int> &min, vector<int> currPath, const int &max, const int *coins, const int &numCoins, int currentSum)
{
   bool vector_incremented = false; // Flag that tells if the size of currPath has incremented or not

   for (int i = 0; i < numCoins; i++)
   {
      if (currentSum == max && currPath.size() < min.size()) // If currentpath
      {
         min = currPath;
      }

      if (!vector_incremented) // Made to only increment currPath once
      {
         vector_incremented = true;
         currPath.resize(currPath.size()+1);
      }

      if (currentSum + coins[i] <= max)
      {
         currPath.back() = coins[i];
         getTroco(min, currPath, max, coins, numCoins, currentSum + coins[i]);
      }
   }

}

void generateSave2(vector<vector<int> > &minCombination, vector<int> currPath, const int &max, const int *coins, const int &numCoins, int currentSum)
{
   for (int i = 0; i < numCoins; i++)
   {
      if ()
      {

      }

   }
}

string calcChange(int m, int numCoins, int *coinValues)
{
   // if (m == 0)
   // return "";
   //
   // if (coinValues[0] > m)
   // return "-";
   //
   // int min = 999;
   // string minPath;
   //
   // generateSave(min, "", minPath, m, coinValues, numCoins, 0, 0);
   //
   // for (int i = 0; i < minPath.length()/2; ++i)
   // {
   //    swap(minPath[i], minPath[minPath.length() - i - 2]);
   // }
   //
   // return minPath;

   vector<int> troco;
   troco.resize(99);

   getTroco(troco, {}, m, coinValues, numCoins, 0);

   print_vector(troco);

   return "hey";
}
