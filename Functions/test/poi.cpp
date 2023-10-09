// poisson_distribution example
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;


int main()
{
	ofstream x ("./boz.txt");
  // construct a trivial random generator engine from a time-based seed:
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);

  poisson_distribution<int> distribution (4);

  //cout << "some Poisson-distributed results (mean=7.1): ";
  int GP = 20;
  int sum = 0;
  double array [GP] ;

  for (int i=0; i<GP; ++i)
  {	
	double b = distribution(generator);
	array[i] = b;
    //x << b << endl;
	sum += b;
  }

  for (int i=0; i<GP; ++i)
  {	
	array[i] = array[i] / sum;

    x << (array[i] * GP) << endl;
  } 

  return 0;
}