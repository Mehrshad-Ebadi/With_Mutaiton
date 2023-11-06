#include "../Headers/Genome.hpp"

void genome::specefication()
{
    for (int i=0 ; i<n ; i++)
    {
        if (ne[temp_net].gn[i].dg_in == 0)
        {
            ne[temp_net].II++;
        }

        if (ne[temp_net].gn[i].dg_out == 0)
        {
            ne[temp_net].UU++;
        }
    }
    
    ne[temp_net].input = new int [ne[temp_net].II];
    ne[temp_net].output = new int [ne[temp_net].UU];
    int i_counter = 0;
    int u_counter = 0;

    for (int i=0 ; i<n ; i++)
    {
        ne[temp_net].gn[i].slf_cntrl = Self_regulation();
        
        if (ne[temp_net].gn[i].dg_out == 0)
        {
            ne[temp_net].output[u_counter] = i;
            u_counter ++ ;
        }

        if (ne[temp_net].gn[i].dg_in == 0)
        {
            ne[temp_net].input[i_counter] = i;
            i_counter++;
        }
    }
}


void genome::du_specefication()
{
    for (int i=0 ; i<nn ; i++)
    {
        if (dn[temp_net].du[i].dg_in == 0)
        {
            dn[temp_net].du_II++;
        }

        if (dn[temp_net].du[i].dg_out == 0)
        {
            dn[temp_net].du_UU++;
        }
    }

    //cout<<"du.."<<dn[temp_net].du_II<<'\t'<<dn[temp_net].du_UU<<'\t'<<temp_net<<endl;
    dn[temp_net].du_input = new int [dn[temp_net].du_II];
    dn[temp_net].du_output = new int [dn[temp_net].du_UU];
    int i_counter = 0;
    int u_counter = 0;

    for (int i=0 ; i<nn ; i++)
    {
        dn[temp_net].du[i].slf_cntrl = Self_regulation();

        if (dn[temp_net].du[i].dg_out == 0)
        {
            dn[temp_net].du_output [u_counter] = i;
            u_counter++ ;
        }
        
        if (dn[temp_net].du[i].dg_in == 0)
        {
            dn[temp_net].du_input[i_counter] = i;
            i_counter++ ;
        }
    }
}