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

double mean_vector(std::vector<double> data)
{
  double mean = 0.;
  for (auto x : data)
  {
    mean += x;
  }
  mean /= data.size();
  return mean;
}

double var_vector(std::vector<double> data)
{
  double mean = 0.;
  double meansq = 0.;
  for (auto x : data)
  {
    mean += x;
    meansq += x*x;
  }
  mean /= data.size();
  meansq /= data.size();
  return meansq - mean*mean;
}

int main()
{
  std::cout << "errors analysis" << std::endl;

  // data
  std::vector<double> data = {
    5.5, 5.2, 5.5,
    5.3, 5.5, 5.3,
    5.1, 5.3, 5.3,
    5.2, 5.6, 5.1,
    5.3, 5.0, 5.1,
    5.0, 5.5, 5.2,
    5.4, 5.2, 5.7,
    5.1, 5.5, 5.2,
    5.3, 5.2, 5.3,
    5.7, 5.3, 3.7
  };
  double err_exp = 0.1;

  int ndata = int(data.size());
  double mean = mean_vector(data);
  double var = var_vector(data);
  double varc = (ndata * var) / (ndata - 1);
  double stdd = std::sqrt(var);
  double stdc = std::sqrt(varc);

  std::cout << "**** Original sample : " << std::endl
            << "Ndata                        : " << ndata << std::endl
            << "Mean                         : " << mean << std::endl
            << "Variance                     : " << var << std::endl
            << "Standard deviation           : " << stdd << std::endl
            << "Corrected variance           : " << varc << std::endl
            << "Corrected standard deviation : " << stdc << std::endl
            << std::endl;

  // chauvenet
  std::cout << "**** Chauvenet rule : " << std::endl;
  std::vector<double> datagood;
  for (int i=0; i < int(data.size()); ++i )
  {
    double x = data[i];
    double t = std::abs((x - mean) / stdc);
    double n = ndata * ( 1 - normal_prob( mean - t * stdc, mean + t * stdc  , mean, stdc) );
    std::cout << "Data " << i << " value " << x << " t " << t << " chauvenet " << n;
    if ( n >= 0.5 )
    {
      datagood.push_back(x);
      std::cout << " OK" << std::endl;
    }
    else
    {
      std::cout << " REJECTED" << std::endl;
    }
  }

  // final analysis
  ndata = int(datagood.size());
  mean = mean_vector(datagood);
  var = var_vector(datagood);
  varc = (ndata * var) / (ndata - 1);
  stdd = std::sqrt(var);
  stdc = std::sqrt(varc);
  double err_stat = stdc / std::sqrt(ndata);
  double err_tot = std::sqrt( err_exp * err_exp + err_stat * err_stat );
  std::cout << "\n**** Filtered sample : " << std::endl
            << "Ndata                        : " << ndata << std::endl
            << "Mean                         : " << mean << std::endl
            << "Variance                     : " << var << std::endl
            << "Standard deviation           : " << stdd << std::endl
            << "Corrected variance           : " << varc << std::endl
            << "Corrected standard deviation : " << stdc << std::endl
            << "Total error                  : " << err_tot << std::endl;
  std::printf("Best value                   : t_best = %.2f +- %.2f\n", mean, err_tot);

  retun 0;
}
