#include "./Gene.hpp"

class Net{
public:
    gene* gn;
    double** adjac;
    int II;
    int UU;
    vector <int> input;
    vector <int> output;
    double fitness;
    double xx;
    bool living;
    int n;
    bool unique;
    int edges;
    int n_isolate;
    
    Net(){};

    ~Net()
    {

        for (int i = 0; i < n; ++i) 
        {
            delete[] adjac[i];
        }
        delete [] adjac;

        delete [] gn;
    }
};
