#include "../Headers/Genome.hpp"

void genome::specefication(int tn)
{
    ne[tn].II = 0;
    ne[tn].UU = 0;
    ne[tn].n_isolate = 0;
    ne[tn].input.clear();
    ne[tn].output.clear();

    for (int i=0 ; i<n ; i++)
    {
        if (ne[tn].gn[i].dg_in == 0 && ne[tn].gn[i].dg_out > 0)
        {
            ne[tn].input.push_back(i);
            ne[tn].II++;
            ne[tn].gn[i].isolated = false;
        }

        if (ne[tn].gn[i].dg_out == 0 && ne[tn].gn[i].dg_in > 0 )
        {
            ne[tn].output.push_back(i);
            ne[tn].UU++;
            ne[tn].gn[i].isolated = false;
        }

        if (ne[tn].gn[i].dg_in == 0 && ne[tn].gn[i].dg_out == 0)
        {
            ne[tn].n_isolate++;
            ne[tn].gn[i].isolated = true;
        }
    }
    
}

void genome::du_specefication(int tn)
{
    dn[tn].II = 0;
    dn[tn].UU = 0;
    dn[tn].n_isolate = 0;
    dn[tn].input.clear();
    dn[tn].output.clear();

    for (int i=0 ; i<nn ; i++)
    {
        if (dn[tn].du[i].dg_in == 0 && dn[tn].du[i].dg_out > 0)
        {
            dn[tn].input.push_back(i);
            dn[tn].II++;
            dn[tn].du[i].isolated = false;
        }

        if (dn[tn].du[i].dg_out == 0 && dn[tn].du[i].dg_in > 0 )
        {
            dn[tn].output.push_back(i);
            dn[tn].UU++;
            dn[tn].du[i].isolated = false;
        }

        if (dn[tn].du[i].dg_in == 0 && dn[tn].du[i].dg_out == 0)
        {
            dn[tn].n_isolate++;
            dn[tn].du[i].isolated = true;
        }
    }
}