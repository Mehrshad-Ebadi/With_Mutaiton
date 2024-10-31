#include "./Gene.hpp"

class Net
{
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
        bool occ;
        int n;
        bool unique;
        int edges;
        int n_isolate;
        int nm_mutation;
        
        Net(){};

    ~Net()
    {

        for (int i = 0; i < n; ++i) 
        {
            delete[] adjac[i];
            input.clear();
            output.clear();
        }
        delete [] adjac;

        delete [] gn;
    }
};
