#include "./Gene.hpp"

class Net{
public:
    gene* gn;
    double** adjac;
    int II;
    int UU;
    int * output;
    int * input;
    double fitness;
    double xx;
    bool living;
    int n;
    bool unique;
    int edges;
    
    Net(){};

    ~Net()
    {
        delete []output;
        delete []input;

        for (int i = 0; i < n; ++i) 
        {
            delete[] adjac[i];
        }
        delete [] adjac;

        delete [] gn;
    }
};
