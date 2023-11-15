#include "./duplicated.hpp"

class dNet
{
    public:
        
        dupli* du;
        double** du_adjac;
        int du_II;
        int du_UU;
        int * du_output;
        int * du_input;
        double fitness;
        double XX;
        bool living;
        int nn;
        bool unique;
        
        dNet(){};
        
    ~dNet()
            
    {
        delete []du_output;
        delete []du_input;

        for (int i = 0; i < nn ; ++i) 
        {
            delete[] du_adjac[i];
        }
        delete [] du_adjac;

        delete [] du;
    }
};