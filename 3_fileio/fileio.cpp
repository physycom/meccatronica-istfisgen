/*
file input/output
*/

#include <iostream>
#include <fstream>
#include <vector>

int main()
{
  std::vector<double> x,y;
  std::vector<int> id;
  std::ifstream fin("data.csv");
  std::string line;
  double xi, yi;
  int idi;

  // read file line by line and store values
  std::getline(fin, line); // skip header
  while( std::getline(fin, line) ) {
    std::sscanf(line.c_str(), "%d;%lf;%lf", &idi, &xi, &yi);
    x.push_back(xi);
    y.push_back(yi);
    id.push_back(idi);
  }
  std::cout << "Read and stored " << x.size() << " data" << std::endl;

  // write data to file
  std::ofstream fout("data_copy_cpp.csv");
  char sep = '\t';
  fout << "INDEX" << sep << "X" << sep << "Y" << std::endl;
  for (int i = 0; i < int(x.size()); ++i) {
    fout << id[i] << sep << x[i] << sep << y[i] << std::endl;
  }

  // final clean up
  fin.close();
  fout.close();

  return 0;
}
