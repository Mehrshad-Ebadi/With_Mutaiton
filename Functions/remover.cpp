#include "../Headers/Genome.hpp"


void genome::memory_Deleter()
{
    delete [] output;
    delete [] input;
    
    for (int F=0 ; F<n ; F++)
    {
        gn[F].dg_in = 0;
        gn[F].dg_out = 0;
        gn[F].nghbrs.clear();
        gn[F].Connected.clear();
        gn[F].weights = 0;

        for (int j=0 ; j<n ; j++)
        { adjac[F][j] = 0; }
    }
    
    II = 0;
    UU = 0;    
    
}

void genome::du_memory_Deleter()
{
    delete [] du_input;
    delete [] du_output;

    du_II = 0;
    du_UU = 0;
    
    for (int F=0 ; F<nn ; F++)
    {
        du[F].dg_in = 0;
        du[F].dg_out = 0;     
        du[F].nghbrs.clear();
        du[F].Connected.clear();
        du[F].nghbrs.shrink_to_fit();
        du[F].Connected.shrink_to_fit();
        du[F].weights = 0;

        for (int j=0 ; j<nn ; j++)
        { du_adjac[F][j] = 0; }
    }
    
    
}