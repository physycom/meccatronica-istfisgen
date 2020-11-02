/*
std::erf tutorial
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// function to evaluate probability related to normal distribution
// Parameters:
//  a = left integration boundary
//  b = right integration boundary
//  X = normal distribution mean value
//  s = normal distribution standard deviation
// Returns:
//  p = probability in the interval [a,b] for the normal distribution with mean=X and stddev=s
double normal_prob(double a, double b, double X, double s)
{
  // input check
  if ( a > b )
  {
    double temp = a;
    b = a;
    a = temp;
  }

  // normalized variables
  double ya = (a - X) / (s * std::sqrt(2.) );
  double yb = (b - X) / (s * std::sqrt(2.) );

  // compute probability using std::erf
  double p = 0.5 * (std::erf(yb) - std::erf(ya));
  return p;
}

int main()
{
  std::cout << "std::erf tutorial" << std::endl;

  // normal distribution parameters
  double X, s;
  X = 5.3;
  s = 0.7;

  // collection of intervals for probability evaluation
  double inf = std::numeric_limits<double>::infinity(); // modern c++ can handle the concept of infinity
  std::vector<std::vector<double>> intervals =
  {
    {X-s, X+s},
    {X-2*s, X+2*s},
    {X-3*s, X+3*s},
    {X+s, X+2*s},
    {X-2*s, X-s},
    {X, inf},
    {-inf, inf}
  };

  // probability evaluation
  for ( const auto &i : intervals )
  {
    std::cout << "P( " << i[0] << " < x < " << i[1] << " ) = " << normal_prob(i[0], i[1], X, s) << std::endl;
  }

  return 0;
}
