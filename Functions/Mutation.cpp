#include "../Headers/Genome.hpp"

void genome::Mutation()
{
    int s = temp_net;
    double nw_wght  = chance_changing_weight;    //new weight
    //double delete_nd   = 0.0003;  // delete a node  
    //double dublict_nd = 0.0002;   //duplicated a node
    double rwrng_nw_cnnctn = chance_of_new_connetion;
    double rwrng_dl_cnnctn = chance_of_del_connection;

    for (int i=0 ; i<n ; i++)             
    {
        if (ne[s].gn[i].nghbrs.size() != 0)
        {
            if (ran2(&iseed) < nw_wght)                 //chance of new weight
            {
                int f = ran2(&iseed) * ne[s].gn[i].nghbrs.size();
                f = ne[s].gn[i].nghbrs[f];

                ne[s].adjac [i][f] = gasdev(&iseed);
            }

            if (ran2(&iseed) < rwrng_nw_cnnctn)
            {
                bool temmpy = true;

                while (temmpy)
                {
                    int f = ran2(&iseed) * n;
                    if (ne[s].adjac [i][f] == 0)
                    {
                        connect(i, f, gasdev(&iseed), s);
                        temmpy = false;
                    }                
                }

            }

            if (ran2(&iseed) < rwrng_dl_cnnctn)
            {
                int f = ran2(&iseed) * ne[s].gn[i].nghbrs.size();
                int FE = ne[s].gn[i].nghbrs[f];
                ne[s].gn[i].nghbrs.erase(ne[s].gn[i].nghbrs.begin() + f);
                ne[s].adjac[i][FE] = 0;
                
                
                auto it = find (ne[s].gn[FE].Connected.begin(), ne[s].gn[FE].Connected.end(), i);
                
                ne[s].gn[FE].Connected.erase(it);
            }
        }
    }

    
}