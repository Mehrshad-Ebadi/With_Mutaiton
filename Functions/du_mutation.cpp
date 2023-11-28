#include "../Headers/Genome.hpp"

void genome::du_Mutation()
{
    int s = temp_net;
    double equ_mt= 2.0;  //by dividing all mutation rate of the single networks by this value, we make the mutaiton rate of the single and doubles identical to each other
    double nw_wght  = chance_changing_weight / equ_mt;    //new weight
    
    double rwrng_nw_cnnctn = chance_of_new_connetion / equ_mt;
    double rwrng_dl_cnnctn = chance_of_del_connection / equ_mt;

    for (int i=0 ; i<nn ; i++)             
    {
        if (dn[s].du[i].nghbrs.size() != 0)
        {
            if (ran2(&iseed) < nw_wght)                 //chance of new weight
            {
                int f = ran2(&iseed) * dn[s].du[i].nghbrs.size();
                f = dn[s].du[i].nghbrs[f];
                dn[s].du_adjac [i][f] = gasdev(&iseed);
            }

            if (ran2(&iseed) < rwrng_nw_cnnctn && dn[s].du[i].nghbrs.size() < n)
            {
                bool temmpy = true;

                while (temmpy)
                {
                    int f = ran2(&iseed) * nn;
                    if (dn[s].du_adjac [i][f] == 0)
                    {
                        du_connect(i, f, gasdev(&iseed),s);
                        temmpy = false;
                    }                
                }

            }

            if (ran2(&iseed) < rwrng_dl_cnnctn)
            {
                int f = ran2(&iseed) * dn[s].du[i].nghbrs.size();
                int FE = dn[s].du[i].nghbrs[f];
                dn[s].du[i].nghbrs.erase(dn[s].du[i].nghbrs.begin() + f);
                dn[s].du_adjac[i][FE] = 0;
                dn[s].edges --;
                auto it = find (dn[s].du[FE].Connected.begin(), dn[s].du[FE].Connected.end(), i);
                
                dn[s].du[FE].Connected.erase(it);
            }
        }
    }    
}