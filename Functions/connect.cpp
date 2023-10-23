#include "../Headers/Genome.hpp"

void genome::connect (int i, int j, double Wgh)
{

    adjac[i][j] = Wgh;
    gn[i].dg_out++;
    gn[i].nghbrs.push_back(j);
    
    gn[j].dg_in++;
    gn[j].Connected.push_back(i);
    
}


void genome::du_connect(int i, int j, double wgh)
{
    du_adjac[i][j] = wgh;
    du[i].dg_out++;
    du[i].nghbrs.push_back(j);

    du[j].dg_in++;
    du[j].Connected.push_back(i);
}