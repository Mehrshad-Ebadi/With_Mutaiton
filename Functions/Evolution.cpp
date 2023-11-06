#include "../Headers/Genome.hpp"


void genome::Evolution(double evolve)
{   
    int s = temp_net;
    if (ne[s].II > 0)
    {
        cout<<"selec="<<ne[s].input[0]<<endl;
        selected_node = ne[s].input[0];
        cout<<"A_selec="<<selected_node<<endl;
        ne[s].gn[selected_node].weights = evolve;
         
        for (int i=0 ; i<ne[s].gn[selected_node].nghbrs.size() ; i++)
        {
            int node2 = ne[s].gn[selected_node].nghbrs[i];
            double VV = 0;   
            
            for (int GH=0 ; GH < ne[s].gn[node2].Connected.size(); GH++)
            {
                int gh = ne[s].gn[node2].Connected[GH];
                VV += double(ne[s].gn[gh].weights * ne[s].adjac[gh][node2]);
            }
            
            ne[s].gn[node2].weights = The_Function(VV);
            ne[s].gn[node2].nm_up ++;
            updater (node2);
        }
    }

    else { ne[s].living = false; }
}

void genome::updater (int nodex)
{   
    int s = temp_net;
    
    if (ne[s].gn[nodex].nm_up <= ne[s].gn[nodex].slf_cntrl)
    {
        for (int i=0 ; i<ne[s].gn[nodex].nghbrs.size() ; i++)
        {   
            double values = 0;
            int node4 = ne[s].gn[nodex].nghbrs[i];

            for (int GH=0 ; GH < ne[s].gn[node4].Connected.size(); GH++)
            {
                int gh = ne[s].gn[node4].Connected[GH];
                values += double(ne[s].gn[gh].weights * ne[s].adjac[gh][node4]);
            }

            ne[s].gn[node4].weights = The_Function(values);
            ne[s].gn[node4].nm_up ++;
            updater (node4);
        }
    }
}
