#include "../Headers/Genome.hpp"


void genome::Evolution(double evolve)
{   
    if (II > 0)
    {
        selected_node = input[0];
        for (int i=0 ; i< n ; i++) gn[i].nm_up = 0;
        gn[selected_node].weights = evolve;
         
        for (int i=0 ; i<gn[selected_node].nghbrs.size() ; i++)
        {
            int node2 = gn[selected_node].nghbrs[i];
            double VV = 0;   
            
            for (int GH=0 ; GH < gn[node2].Connected.size(); GH++)
            {
                int gh = gn[node2].Connected[GH];
                VV += double(gn[gh].weights * adjac[gh][node2]);
            }
            gn[node2].weights = The_Function(VV);
            updater (node2);
        }
    }

}

void genome::updater (int nodex)
{   
    if (gn[nodex].nm_up <= gn[nodex].slf_cntrl)
    {
        for (int i=0 ; i<gn[nodex].nghbrs.size() ; i++)
        {   
            double values = 0;
            int node4 = gn[nodex].nghbrs[i];

            for (int GH=0 ; GH < gn[node4].Connected.size(); GH++)
            {
                int gh = gn[node4].Connected[GH];
                values += double(gn[gh].weights * adjac[gh][node4]);
            }

            gn[node4].weights = The_Function(values);
            gn[node4].nm_up ++;
            updater (node4);
        }
    }
}
