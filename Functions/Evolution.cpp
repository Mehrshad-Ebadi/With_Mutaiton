#include "../Headers/Genome.hpp"


void genome::Evolution(double evolve, int temp_net)
{   
    int s = temp_net;

    if (ne[s].II > 0)
    {
        selected_node = ne[s].input[0];
        ne[s].gn[selected_node].weights = evolve;

        for (int i=0; i<n ; i++)
        {
            ne[s].gn[i].updte_list.clear();
            ne[s].gn[i].updte_list.shrink_to_fit();
            ne[s].gn[i].updte_list = ne[s].gn[i].nghbrs;
        }

        int d=0;
        while (d < ne[s].gn[selected_node].updte_list.size())
        {
            int node2 = ne[s].gn[selected_node].updte_list[d];
            double VV = 0;   
            if (ne[s].gn[node2].nm_up > ne[s].gn[node2].slf_cntrl)
            {
                ne[s].gn[selected_node].updte_list.erase(ne[s].gn[selected_node].updte_list.begin() + d);
            }

            else 
            {
                for (int GH=0 ; GH < ne[s].gn[node2].Connected.size(); GH++)
                {
                    int gh = ne[s].gn[node2].Connected[GH];
                    VV += double(ne[s].gn[gh].weights * ne[s].adjac[gh][node2]);
                }

                ne[s].gn[node2].weights = The_Function(VV);
                ne[s].gn[node2].nm_up ++;
                updater (node2, s);
                d++;
            }
        }
    }
}

void genome::updater (int nodex, int temp_net)
{   
    int s = temp_net;
    
    int i=0;
    
    while (i < ne[s].gn[nodex].updte_list.size())
    {   
        double values = 0;
        int node4 = ne[s].gn[nodex].updte_list[i];
        
        if (ne[s].gn[node4].nm_up > ne[s].gn[node4].slf_cntrl)
        {
            ne[s].gn[nodex].updte_list.erase(ne[s].gn[nodex].updte_list.begin() + i);
        }

        else 
        {
            for (int GH=0 ; GH < ne[s].gn[node4].Connected.size(); GH++)
            {
                int gh = ne[s].gn[node4].Connected[GH];
                values += double(ne[s].gn[gh].weights * ne[s].adjac[gh][node4]);
            }

            ne[s].gn[node4].weights = The_Function(values);
            ne[s].gn[node4].nm_up ++;
            i++;
            updater (node4, s);
        }
    }
    
}
