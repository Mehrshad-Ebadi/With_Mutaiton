#include "../Headers/Genome.hpp"

void genome::Mutation(int temp_net)
{
    int s = temp_net;
    //double delete_nd   = 0.0003;  // delete a node  
    //double dublict_nd = 0.0002;   //duplicated a node
    double nw_wght  = chance_changing_weight;    //new weight
    
    for (int i=0 ; i<n ; i++)             
    {
        if (ran2(&iseed) < nw_wght && ne[s].gn[i].nghbrs.size() > 0)                 //chance of new weight
        {
            int f = ran2(&iseed) * ne[s].gn[i].nghbrs.size();
            f = ne[s].gn[i].nghbrs[f];
            ne[s].nm_mutation++;
            ne[s].adjac [i][f] = gasdev(&iseed);
        }

    }
}