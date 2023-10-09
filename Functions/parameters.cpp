#include "../Headers/Genome.hpp"

double genome::parameters ()
{
    xx = 0;
    for (int i=0 ; i<UU ; i++) 
    {
        int j = output[i];
        xx += gn[j].weights;
    }

    xx = double (xx / UU);
    return xx;
}


double genome::du_parameters ()
{
    XX = 0;
    
    for (int i=0 ; i<du_UU ; i++) 
    {
        int j = du_output[i];
        XX += du[j].weights;
    }

    XX = double (XX / du_UU);
    return XX;
}    
