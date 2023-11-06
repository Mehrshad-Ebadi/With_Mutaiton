#include "../Headers/Genome.hpp"


void genome::du_Evolution(double evolve)
{   
    int s = temp_net;

    if (dn[s].du_II > 0)
    {        
        dn[s].du[selected_node].weights = evolve;
         
        for (int i=0 ; i<dn[s].du[selected_node].nghbrs.size() ; i++)
        {
            int node2 = dn[s].du[selected_node].nghbrs[i];
            double VV = 0;   
            
            for (int GH=0 ; GH < dn[s].du[node2].Connected.size(); GH++)
            {
                int gh = dn[s].du[node2].Connected[GH];
                VV += double(dn[s].du[gh].weights * dn[s].du_adjac[gh][node2]);
            }
            
            dn[s].du[node2].weights = The_Function(VV);
            dn[s].du[node2].nm_up++;
            du_updater (node2);
        }
    }
    
    else { dn[s].living = false; }

}

void genome::du_updater (int nodex)
{   
    int s = temp_net;

    if (dn[s].du[nodex].nm_up <= dn[s].du[nodex].slf_cntrl)
    {
        for (int i=0 ; i<dn[s].du[nodex].nghbrs.size() ; i++)
        {   
            double values = 0;
            int node4 = dn[s].du[nodex].nghbrs[i];

            for (int GH=0 ; GH < dn[s].du[node4].Connected.size(); GH++)
            {
                int gh = dn[s].du[node4].Connected[GH];
                values += double(dn[s].du[gh].weights * dn[s].du_adjac[gh][node4]);
            }

            dn[s].du[node4].weights = The_Function(values);
            dn[s].du[node4].nm_up ++;
            du_updater (node4);
        }
    }
}
