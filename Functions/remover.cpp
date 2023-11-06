#include "../Headers/Genome.hpp"


void genome::memory_Deleter()
{
    int s = temp_net;
    delete [] ne[s].output;
    delete [] ne[s].input;
    
    for (int F=0 ; F<n ; F++)
    {
        ne[s].gn[F].dg_in = 0;
        ne[s].gn[F].dg_out = 0;
        ne[s].gn[F].nghbrs.clear();
        ne[s].gn[F].Connected.clear();
        ne[s].gn[F].weights = 0;
        ne[s].gn[F].nm_up = 0;

        for (int j=0 ; j<n ; j++)
        { ne[s].adjac[F][j] = 0; }
    }
    
    ne[s].II = 0;
    ne[s].UU = 0;    
    
}

void genome::du_memory_Deleter()
{
    int s = temp_net;
    delete [] dn[s].du_input;
    delete [] dn[s].du_output;

    dn[s].du_II = 0;
    dn[s].du_UU = 0;
    
    for (int F=0 ; F<nn ; F++)
    {
        dn[s].du[F].dg_in = 0;
        dn[s].du[F].dg_out = 0;     
        dn[s].du[F].nghbrs.clear();
        dn[s].du[F].Connected.clear();
        dn[s].du[F].weights = 0;
        dn[s].du[F].nm_up = 0;

        for (int j=0 ; j<nn ; j++)
        { dn[s].du_adjac[F][j] = 0; }
    }
    
}
