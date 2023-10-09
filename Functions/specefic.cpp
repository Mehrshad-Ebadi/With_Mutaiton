#include "../Headers/Genome.hpp"

void genome::specefication()
{

    II = 0;
    UU = 0;

    for (int i=0 ; i<n ; i++)
    {
        if (gn[i].dg_in == 0)
        {
            II++;
        }

        if (gn[i].dg_out == 0)
        {
            UU++;
        }
    }

    input = new int [II];
    output = new int [UU];
    int i_counter = 0;
    int u_counter = 0;

    for (int i=0 ; i<n ; i++)
    {
        if (gn[i].dg_out == 0)
        {
            output[u_counter] = i;
            u_counter ++ ;
        }

        if (gn[i].dg_in == 0)
        {
            input[i_counter] = i;
            i_counter++;
        }

        for (int j=0 ; j<n ; j++)
        {
            gn[i].slf_cntrl = Self_regulation();

            if (adjac[j][i] != 0)
            {
                gn[i].Connected.push_back(j);
            }
        }
    }
}


void genome::du_specefication()
{
    du_II = 0;
    du_UU = 0;

    for (int i=0 ; i<nn ; i++)
    {
        if (du[i].dg_in == 0)
        {
            du_II++;
        }

        if (du[i].dg_out == 0)
        {
            du_UU++;
        }
    }

    du_input = new int [du_II];
    du_output = new int [du_UU];
    int i_counter = 0;
    int u_counter = 0;

    for (int i=0 ; i<nn ; i++)
    {
        if (du[i].dg_in == 0)
        {
            du_input[i_counter] = i;
            i_counter++ ;
        }

        if (du[i].dg_out == 0)
        {
            du_output [u_counter] = i;
            u_counter++ ;
        }

        for (int j=0 ; j<nn ; j++)
        {
            if (du_adjac[j][i] != 0)
            {
                du[i].Connected.push_back(j);
            }
        }
    }

}