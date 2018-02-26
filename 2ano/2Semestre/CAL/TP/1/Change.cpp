/*
* Change.cpp
*/

#include "Change.h"
#include <string>
#include <iostream>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>

template<class T>
void append(vector<T> &a, const vector<T> &b)
{
   for (int i = 0; i < b.size(); ++i)
   {
      a.push_back(b[i]);
   }
}

template<class T>
vector<T> addVector(const vector<T> &a, const vector<T> &b)
{
   vector<T> res;

   for (int i = 0; i < a.size(); ++i)
   {
      res.push_back(a[i]);
   }

   for (int i = 0; i < b.size(); ++i)
   {
      res.push_back(b[i]);
   }

   return res;
}


template<class T>
void print_array(const T input[], const int &size)
{
   for (int i = 0; i < size; i++)
   {
      cout << input[i] << ' ';
   }
   cout << "\n\n";
}

template<class T>
void print_vector(const vector<T> &input)
{
   for (int i = 0; i < input.size(); i++)
   {
      cout << input[i] << ' ';
   }
}

template<class T>
void print_vector(const vector<vector<T> > &input)
{
   for (int i = 0; i < input.size(); i++)
   {
      print_vector(input[i]);
      cout << '\n';
   }
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

vector<int> getTroco(const int &max, const int *coins, const int &numCoins)
{
   vector<int> res;
   res.resize(99);

   getTroco(res, {}, max, coins, numCoins, 0);

   return res;
}

vector<vector<int> > generateSave2(const int &max, const int *coins, const int &numCoins)
{
   vector<vector<int> > minCombination;
   minCombination.resize(max+1);
   minCombination.front() = {};

   vector<int> min;

   for (int i = 1; i <= max; ++i)
   {
      min.resize(0);

      //print_vector(minCombination);

      for (int j = 0; j < numCoins; j++)
      {

         if (i - coins[j] >= 0)
         {
            if (min.size() == 0)
               min = addVector(minCombination[i - coins[j]], {coins[j]});
            else if (minCombination[i - coins[j]].size() + 1 < min.size())
               min = addVector(minCombination[i - coins[j]], {coins[j]});
         }

      }

      if (min.size() == 0)
         min = getTroco(max, coins, numCoins);

      minCombination[i] = min;
   }

   return minCombination;
}

vector<vector<int> > generateSave3(const int &max, const int *coins, const int &numCoins)
{
   vector<vector<int> > minCombination;
   minCombination.resize(max+1);
   minCombination.front() = {};

   vector<int> min;

   for (int i = 1; i <= max; ++i)
   {
      min.resize(0);

      //print_vector(minCombination);

      for (int j = 0; j < numCoins; j++)
      {

         if (i - coins[j] >= 0)
         {
            if (min.size() == 0)
               min = addVector(minCombination[i - coins[j]], {coins[j]});
            else if (minCombination[i - coins[j]].size() + 1 < min.size())
               min = addVector(minCombination[i - coins[j]], {coins[j]});
         }

      }

      if (min.size() == 0)
         min = getTroco(max, coins, numCoins);

      minCombination[i] = min;
   }

   return minCombination;
}

string calcChange(int m, int numCoins, int *coinValues)
{
   if (m == 0)
   return "";
   
   if (coinValues[0] > m)
   return "-";
   
   string minPath;
   int ola;

   generateSave(ola, "", minPath, m, coinValues, numCoins, 0, 0);

   // for (int i = 0; i < res.size(); ++i)
   // {
   //    minPath.push_back(res[i] + '0');
   //    minPath.push_back(';');
   // }

   return minPath;
}
