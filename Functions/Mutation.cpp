#include "../Headers/Genome.hpp"

void genome::Mutation(int temp_net)
{
    int s = temp_net;
    //double delete_nd   = 0.0003;  // delete a node  
    //double dublict_nd = 0.0002;   //duplicated a node
    double nw_wght         = chance_changing_weight;    //new weight
    double rwrng_nw_cnnctn = chance_changing_weight;
    double rwrng_dl_cnnctn = chance_changing_weight;
    
    for (int i=0 ; i<n ; i++)             
    {
        if (ran2(&iseed) < nw_wght && ne[s].gn[i].nghbrs.size() > 0)                 //chance of new weight
        {
            int f = ran2(&iseed) * ne[s].gn[i].nghbrs.size();
            f = ne[s].gn[i].nghbrs[f];

            ne[s].adjac [i][f] = gasdev(&iseed);
        }

        if (ran2(&iseed) < rwrng_nw_cnnctn && ne[s].gn[i].nghbrs.size() < n)
        {
            bool temmpy = true;
            while (temmpy)
            {
                int f = ran2(&iseed) * n;
                if (ne[s].adjac [i][f] == 0)
                {
                    connect(i, f, gasdev(&iseed), s);
                    specefication(s);
                    temmpy = false;
                }
            }
        }

        if (ran2(&iseed) < rwrng_dl_cnnctn && ne[s].gn[i].nghbrs.size() > 0)
        {
            int f = ran2(&iseed) * ne[s].gn[i].nghbrs.size();
            int FE = ne[s].gn[i].nghbrs[f];
            ne[s].gn[i].nghbrs.erase(ne[s].gn[i].nghbrs.begin() + f);
            ne[s].adjac[i][FE] = 0;
            ne[s].edges --;
            ne[s].gn[i].dg_out --;
            
            auto it = find (ne[s].gn[FE].Connected.begin(), ne[s].gn[FE].Connected.end(), i);
            
            ne[s].gn[FE].Connected.erase(it);
            ne[s].gn[FE].dg_in --;
            
            specefication(s);
        }
    }
}