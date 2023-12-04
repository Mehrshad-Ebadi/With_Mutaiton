#include "./duplicated.hpp"

class dNet
{
    public:
        
        dupli* du;
        double** du_adjac;
        int II;
        int UU;
        vector <int> input;
        vector <int> output;
        double fitness;
        double XX;
        bool living;
        int nn;
        bool unique;
        int edges;
        int n_isolate;
        
        dNet(){};
        
    ~dNet()
            
    {

        for (int i = 0; i < nn ; ++i) 
        {
            delete[] du_adjac[i];
        }
        delete [] du_adjac;

        delete [] du;
    }
};