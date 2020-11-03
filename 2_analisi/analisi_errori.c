/*
error analysis
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Description:
//  Function to evaluate probability related to normal distribution
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

  // compute probability using std::erf
  double p = 0.5 * (erf(yb) - erf(ya));
  return p;
}

// Description:
//  Function to evaluate the mean value of an array of double
// Parameters:
//  data = pointer to values
//  ndata = number of values stored in data
// Returns:
//  mean = the arithmetic mean
double mean(double data[], int ndata)
{
  double m = 0.;
  int i = 0;

  // accumulate sum of values
  for (i = 0; i < ndata; ++i) {
    m += data[i];
  }

  // normalization
  m /= ndata;

  return m;
}

// Description:
//  Function to evaluate the variance of an array of double
// Parameters:
//  data = pointer to values
//  ndata = number of values stored in data
// Returns:
//  var = statistical variance
double variance(double data[], int ndata)
{
  int i;
  double mean, meansq, var;
  mean = 0.;
  meansq = 0.;

  // accumulate sum of values and sum of squared values
  for (i = 0; i < ndata; ++i) {
    mean += data[i];
    meansq += data[i] * data[i];
  }

  // normalization
  mean /= ndata;
  meansq /= ndata;

  // variance evaluation using formula
  // var(x) = <x^2> - <x>^2
  var = meansq - mean*mean;

  return var;
}

int main()
{
  printf("errors analysis\n");
  int i, ndata, good_counter, good_idx;
  double m, var, varc, stdd, stdc;
  double err_exp, err_stat, err_tot;
  double x, t, n;
  double *data_status, *datagood;

  // data
  double data[] = {
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
  err_exp = 0.1;

  // original sample analysis
  ndata = sizeof(data) / sizeof(double);
  m = mean(data, ndata);
  var = variance(data, ndata);
  varc = (ndata * var) / (ndata - 1);
  stdd = sqrt(var);
  stdc = sqrt(varc);

  printf("**** Original sample : \n");
  printf("Ndata                        : %d\n", ndata);
  printf("Mean                         : %f\n", m);
  printf("Variance                     : %f\n", var);
  printf("Standard deviation           : %f\n", stdd);
  printf("Corrected variance           : %f\n", varc);
  printf("Corrected standard deviation : %f\n\n", stdc);

  // chauvenet
  printf("**** Chauvenet rule : \n");

  // create support array to store chauvenet check result
  // 0 = rejected value
  // 1 = accepted value
  data_status = malloc(ndata * sizeof(double));     // reserve dynamical memory
  good_counter = 0;

  // loop over data and perform chauvenet check
  for (i = 0; i < ndata; ++i)
  {
    // chauvenet parameters
    x = data[i];
    t = abs((x - m) / stdc);
    n = ndata * ( 1 - normal_prob( m - t * stdc, m + t * stdc  , m, stdc) );
    printf("Data %d value %f t %f chauvenet %f", i, x, t, n);

    // check
    if ( n >= 0.5 )
    {
      data_status[i] = 1;
      printf(" OK\n");
      ++good_counter;
    }
    else
    {
      data_status[i] = 0;
      printf(" REJECTED\n");
    }
  }

  // copy good data to new array
  datagood = (double*) malloc(good_counter * sizeof(double));
  good_idx = 0;
  for (i = 0; i < ndata; ++i) {
    if (data_status[i] == 1) { // chavenet-accepted values
      datagood[good_idx] = data[i]; // store good value in datagood
      ++good_idx;                   // increase index
    }
  }

  // final sample analysis
  ndata = good_counter;
  m = mean(datagood, ndata);
  var = variance(datagood, ndata);
  varc = (ndata * var) / (ndata - 1);
  stdd = sqrt(var);
  stdc = sqrt(varc);
  err_stat = stdc / sqrt(ndata);
  err_tot = sqrt( err_exp * err_exp + err_stat * err_stat );
  printf("\n**** Filtered sample : \n");
  printf("Ndata                        : %d\n", ndata);
  printf("Mean                         : %f\n", m);
  printf("Variance                     : %f\n", var);
  printf("Standard deviation           : %f\n", stdd);
  printf("Corrected variance           : %f\n", varc);
  printf("Corrected standard deviation : %f\n\n", stdc);
  printf("Best value                   : t_best = %.2f +- %.2f\n", m, err_tot);

  // final clean up
  free(data_status);
  free(datagood);
  return 0;
}
