#include "../Headers/Genome.hpp"


void genome::du_Evolution(double evolve, int temp_net)
{   
    int s = temp_net;
    
    for (int i=0; i<nn ; i++)
    {
        dn[s].du[i].updte_list.clear();
        dn[s].du[i].updte_list.shrink_to_fit();
        dn[s].du[i].updte_list = dn[s].du[i].nghbrs;
        dn[s].du[i].nm_up = 0;
        dn[s].du[i].weights = 0;
    }
    
    if (dn[s].II > 0)
    {
        selected_node = dn[s].input[0];
        dn[s].du[selected_node].weights = evolve;
        int d=0;

        while (d < dn[s].du[selected_node].updte_list.size())
        {
            int node2 = dn[s].du[selected_node].updte_list[d];
            double VV = 0;   
            if (dn[s].du[node2].nm_up > dn[s].du[node2].slf_cntrl)
            {
                dn[s].du[selected_node].updte_list.erase(dn[s].du[selected_node].updte_list.begin() + d);
            }

            else 
            {
                for (int GH=0 ; GH < dn[s].du[node2].Connected.size(); GH++)
                {
                    int gh = dn[s].du[node2].Connected[GH];
                    VV += double(dn[s].du[gh].weights * dn[s].du_adjac[gh][node2]);
                }

                dn[s].du[node2].weights = The_Function(VV);
                dn[s].du[node2].nm_up ++;
                du_updater (node2, s);
                d++;
            }
        }
    }
}

void genome::du_updater (int nodex, int temp_net)
{   
    int s = temp_net;
    
    int i=0;
    while (i < dn[s].du[nodex].updte_list.size())
    {   
        double values = 0;
        int node4 = dn[s].du[nodex].updte_list[i];
        
        if (dn[s].du[node4].nm_up > dn[s].du[node4].slf_cntrl)
        {
            dn[s].du[nodex].updte_list.erase(dn[s].du[nodex].updte_list.begin() + i);
        }

        else 
        {
            for (int GH=0 ; GH < dn[s].du[node4].Connected.size(); GH++)
            {
                int gh = dn[s].du[node4].Connected[GH];
                values += double(dn[s].du[gh].weights * dn[s].du_adjac[gh][node4]);
            }

            dn[s].du[node4].weights = The_Function(values);
            dn[s].du[node4].nm_up ++;
            du_updater (node4, s);
            i++;
        }
    }
    
}
