/*
file input/output
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *fp, *fpout;
  char *line = NULL, sep;
  size_t len = 0, linenum = 0;
  ssize_t nread;
  double xi, yi, *x, *y;
  int i, idi, *id, ndata;

  // open data file with safety check
  fp = fopen("data.csv", "r");
  if (fp == NULL) {
    printf("ERROR file not found\n");
    return 1;
  }

  // read file once to count line number in order to reserve memory
  while ((nread = getline(&line, &len, fp)) != -1) ++linenum;
  rewind(fp); // move pointer back to file beginning
  printf("Line number %ld\n", linenum);

  // reserve memory
  x = malloc( linenum * sizeof(double) );
  y = malloc( linenum * sizeof(double) );
  id = malloc( linenum * sizeof(int) );

  // read file line by line and store data in corresponding array
  getline(&line, &len, fp); // skip header
  i = 0;
  while (fscanf(fp, "%d;%lf;%lf", &idi, &xi, &yi) != EOF) {
    x[i] = xi;
    y[i] = yi;
    id[i] = idi;
    ++i;
  }
  ndata = i;
  printf("Read and stored %d data\n", ndata);

  // safely open open new file
  fpout = fopen("data_copy_c.csv", "w");
  if (fpout == NULL) {
    printf("ERROR writing file\n");
    return 2;
  }

  // loop over data and write to file
  sep = ','; // change csv separator
  fprintf(fpout, "INDEX%cX%cY\n", sep, sep);
  for( i = 0; i < ndata; ++i) {
    fprintf(fpout, "%d%c%lf%c%lf\n", id[i], sep, x[i], sep, y[i]);
  }

  // final cleanup
  fclose(fp);
  fclose(fpout);
  if (x) free(x);
  if (y) free(y);
  if (id) free(id);

  return 0;
}