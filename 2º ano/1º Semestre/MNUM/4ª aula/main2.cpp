#include <vector>
#include <iostream>


int main()
{

double x0,y0,xn,yn;

std::cin >> x0 >> y0;

for (size_t i = 1; i <= 50; i++)
{
  std::cout << i << "  " << x0 << "  " << y0 << '\n';
  xn = (y0*y0-5.0)/2.0 - (5 + 2*x0 - 2*x0*((-20) + x0*x0 -y0) -y0*y0)/(2-4*x0*y0);
  yn = x0*x0 -20 - ((-2*((-20) + x0*x0 - y0)) - 2*y0*((-5) -2*x0 +y0*y0))/(2.0-4*x0*y0);
  x0 = xn;
  y0 = yn;
}


return 0;
}
