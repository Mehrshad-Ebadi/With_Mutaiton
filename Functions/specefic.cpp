#include "../Headers/Genome.hpp"

void genome::specefication(int tn)
{
    int TN = tn;
    ne[TN].II = 0;
    ne[TN].UU = 0;
    ne[TN].n_isolate = 0;
    ne[TN].input.clear();
    ne[TN].output.clear();

    for (int i=0 ; i<n ; i++)
    {
        if (ne[TN].gn[i].dg_in == 0 && ne[TN].gn[i].dg_out > 0)
        {
            ne[TN].input.push_back(i);
            ne[TN].II++;
        }

        if (ne[TN].gn[i].dg_out == 0 && ne[TN].gn[i].dg_in > 0 )
        {
            ne[TN].output.push_back(i);
            ne[TN].UU++;
        }

        if (ne[TN].gn[i].dg_in == 0 && ne[TN].gn[i].dg_out == 0)
        {
            ne[TN].n_isolate++;
            ne[TN].gn[i].isolated = true;
        }
    }
    
}

void genome::du_specefication(int tn)
{
    int TN = tn;
    dn[TN].II = 0;
    dn[TN].UU = 0;
    dn[TN].n_isolate = 0;
    dn[TN].input.clear();
    dn[TN].output.clear();

    for (int i=0 ; i<nn ; i++)
    {
        if (dn[TN].du[i].dg_in == 0 && dn[TN].du[i].dg_out > 0)
        {
            dn[TN].input.push_back(i);
            dn[TN].II++;
        }

        if (dn[TN].du[i].dg_out == 0 && dn[TN].du[i].dg_in > 0 )
        {
            dn[TN].output.push_back(i);
            dn[TN].UU++;
        }

        if (dn[TN].du[i].dg_in == 0 && dn[TN].du[i].dg_out == 0)
        {
            dn[TN].n_isolate++;
            dn[TN].du[i].isolated = true;
        }
    }
}