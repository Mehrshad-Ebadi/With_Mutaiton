#include "../Headers/Genome.hpp"

void genome::specefication(int tn)
{
    cout<<"here"<<endl;
    int TN = tn;
    ne[TN].II = 0;
    ne[TN].II = 0;
    ne[TN].n_isolate = 0;

    if (ne[TN].input != nullptr)
    {
        delete [] ne[TN].input;
    }

    if (ne[TN].output != nullptr)
    {
        delete [] ne[TN].output;
    }
    cout<<"here1"<<endl;
    for (int i=0 ; i<n ; i++)
    {
        if (ne[TN].gn[i].dg_in == 0 && ne[TN].gn[i].dg_out != 0)
        {
            ne[TN].II++;
        }

        if (ne[TN].gn[i].dg_out == 0 && ne[TN].gn[i].dg_in != 0 )
        {
            ne[TN].UU++;
        }

        if (ne[TN].gn[i].dg_in == 0 && ne[TN].gn[i].dg_out == 0)
        {
            ne[TN].n_isolate++;
            ne[TN].gn[i].isolated = true;
        }
    }
    
    ne[TN].input = new int [ne[TN].II];
    ne[TN].output = new int [ne[TN].UU];
    int i_counter = 0;
    int u_counter = 0;
    cout<<"here3"<<endl;
    for (int i=0 ; i<n ; i++)
    {
        ne[TN].gn[i].slf_cntrl = Self_regulation();
        
        if (ne[TN].gn[i].dg_out == 0)
        {
            ne[TN].output[u_counter] = i;
            u_counter ++ ;
        }

        if (ne[TN].gn[i].dg_in == 0)
        {
            ne[TN].input[i_counter] = i;
            i_counter++;
        }
    }
}


void genome::du_specefication(int tn)
{
    int TN = tn;
    dn[TN].du_II = 0;
    dn[TN].du_II = 0;
    dn[TN].n_isolate = 0;

    if (dn[TN].du_input != nullptr)
    {
        delete [] dn[TN].du_input;
    }

    if (dn[TN].du_output != nullptr)
    {
        delete [] dn[TN].du_output;
    }

    for (int i=0 ; i<nn ; i++)
    {
        if (dn[TN].du[i].dg_in == 0 && dn[TN].du[i].dg_out != 0)
        {
            dn[TN].du_II++;
        }

        if (dn[TN].du[i].dg_out == 0 && dn[TN].du[i].dg_in != 0 )
        {
            dn[TN].du_UU++;
        }

        if (dn[TN].du[i].dg_in == 0 && dn[TN].du[i].dg_out == 0)
        {
            dn[TN].n_isolate++;
            dn[TN].du[i].isolated = true;
        }
    }

    //cout<<"du.."<<dn[TN].du_II<<'\t'<<dn[TN].du_UU<<'\t'<<TN<<endl;
    dn[TN].du_input = new int [dn[TN].du_II];
    dn[TN].du_output = new int [dn[TN].du_UU];
    int i_counter = 0;
    int u_counter = 0;

    for (int i=0 ; i<nn ; i++)
    {
        dn[TN].du[i].slf_cntrl = Self_regulation();

        if (dn[TN].du[i].dg_out == 0)
        {
            dn[TN].du_output [u_counter] = i;
            u_counter++ ;
        }
        
        if (dn[TN].du[i].dg_in == 0)
        {
            dn[TN].du_input[i_counter] = i;
            i_counter++ ;
        }
    }
}