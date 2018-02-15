#include <iostream>
#include <cmath>


int factorial(int n)
{
int res = 1;

for(int i = 2; i <= n; i++)
{
   res *= i;
}
return res;
}



double func1(int n)
{
   double res = std::exp(1) - 1;
   res *= factorial(n);

int temp1 = 1;
int temp2 = 0;

   for(int i = n; i > 0; i--) 
   {
      temp2 -= temp1;
      temp1 *= i;

   }

return res + temp2;
}

int main()
{
std::cout.precision(17);

std::cout << "\n";

std::cout << func1(25);


std::cout << "\n\n";
return 0;
}
