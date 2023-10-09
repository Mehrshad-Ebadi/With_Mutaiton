#include "../Headers/Genome.hpp"

void genome::connect (int i, int j, double Wgh)
{

    adjac[i][j] = Wgh;
    gn[i].dg_out++;
    gn[j].dg_in++;
    gn[i].nghbrs.push_back(j);
    
}


void genome::du_connect(int i, int j, double wgh)
{
    du_adjac[i][j] = wgh;
    du[i].dg_out++;
    du[j].dg_in++;
    du[i].nghbrs.push_back(j);   
}