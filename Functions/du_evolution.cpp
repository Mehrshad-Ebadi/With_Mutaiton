#include "../Headers/Genome.hpp"


void genome::du_Evolution(double evolve)
{   
    if (du_II > 0)
    {
        selected_node = du_input[0];
        
        for (int i=0 ; i< nn ; i++) du[i].nm_up = 0;
        
        du[selected_node].weights = evolve;
         
        for (int i=0 ; i<du[selected_node].nghbrs.size() ; i++)
        {
            int node2 = du[selected_node].nghbrs[i];
            double VV = 0;   
            
            for (int GH=0 ; GH < du[node2].Connected.size(); GH++)
            {
                int gh = du[node2].Connected[GH];
                VV += double(du[gh].weights * du_adjac[gh][node2]);
            }
            du[node2].weights = The_Function(VV);
            du_updater (node2);
        }
    }

}

void genome::du_updater (int nodex)
{   
    if (du[nodex].nm_up <= du[nodex].slf_cntrl)
    {
        for (int i=0 ; i<du[nodex].nghbrs.size() ; i++)
        {   
            double values = 0;
            int node4 = du[nodex].nghbrs[i];

            for (int GH=0 ; GH < du[node4].Connected.size(); GH++)
            {
                int gh = du[node4].Connected[GH];
                values += double(du[gh].weights * du_adjac[gh][node4]);
            }

            du[node4].weights = The_Function(values);
            du[node4].nm_up ++;
            du_updater (node4);
        }
    }
}
