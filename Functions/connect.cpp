#include "../Headers/Genome.hpp"

void genome::connect (int i, int j, double Wgh, int SH)
{

    ne[SH].adjac[i][j] = Wgh;
    ne[SH].gn[i].dg_out++;
    ne[SH].gn[i].nghbrs.push_back(j);
    
    ne[SH].gn[j].dg_in++;
    ne[SH].gn[j].Connected.push_back(i);
    ne[SH].edges ++;
    
}


void genome::du_connect(int i, int j, double wgh, int SH)
{
    dn[SH].du_adjac[i][j] = wgh;
    dn[SH].du[i].dg_out++;
    dn[SH].du[i].nghbrs.push_back(j);

    dn[SH].du[j].dg_in++;
    dn[SH].du[j].Connected.push_back(i);
    dn[SH].edges ++;
}