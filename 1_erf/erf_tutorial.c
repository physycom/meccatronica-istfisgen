/*
erf function tutorial
*/

#include <stdio.h>
#include <math.h>

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
  double ya = (a - X) / (s * sqrt(2.) );
  double yb = (b - X) / (s * sqrt(2.) );

  // compute probability using erf
  double p = 0.5 * (erf(yb) - erf(ya));
  return p;
}

int main()
{
  // variables
  int i;

  // normal distribution parameters
  double X, s;
  X = 5.3;
  s = 0.7;

  printf("erf function tutorial\n");

  // collection of intervals for probability evaluation
  double intervals[][2] =
  {
    X-s, X+s,
    X-2*s, X+2*s,
    X-3*s, X+3*s,
    X+s, X+2*s,
    X-2*s, X-s
  };
  int nintervals = sizeof(intervals) / sizeof(double) / 2;

  // probability evaluation
  for (i=0; i < nintervals; ++i)
  {
    printf("P( %f < x < %f ) = %f\n", intervals[i][0], intervals[i][1], normal_prob(intervals[i][0], intervals[i][1], X, s));
  }

  return 0;
}
