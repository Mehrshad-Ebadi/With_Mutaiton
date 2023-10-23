#include "../Headers/Genome.hpp"

void genome::du_Mutation(string du_location)
{
    double equ_mt= 2;  //by dividing all mutation rate of the single networks by this value, we make the mutaiton rate of the single and doubles identical to each other
    double nw_wght  = chance_changing_weight / equ_mt;    //new weight
    
    //double delete_nd   = 0.0003 / equ_mt;  // delete a node  
    //double dublict_nd = 0.0002 / equ_mt;   //duplicated a node
    
    double rwrng_nw_cnnctn = chance_of_new_connetion / equ_mt;
    double rwrng_dl_cnnctn = chance_of_del_connection / equ_mt;
    bool saving_is_ncessary = false;

    for (int i=0 ; i<nn ; i++)             
    {
        if (du[i].nghbrs.size() != 0)
        {
            if (ran2(&iseed) < nw_wght)                 //chance of new weight
            {
                saving_is_ncessary = true;
                
                int f = ran2(&iseed) * du[i].nghbrs.size();
                f = du[i].nghbrs[f];

                du_adjac [i][f] = gasdev(&iseed);
            }

            if (ran2(&iseed) < rwrng_nw_cnnctn)
            {
                saving_is_ncessary = true;
                bool temmpy = true;

                while (temmpy)
                {
                    int f = ran2(&iseed) * nn;
                    if (du_adjac [i][f] == 0)
                    {
                        du_connect(i, f, gasdev(&iseed));
                        temmpy = false;
                    }                
                }

            }

            if (ran2(&iseed) < rwrng_dl_cnnctn)
            {
                saving_is_ncessary = true;
                int f = ran2(&iseed) * du[i].nghbrs.size();
                int FE = du[i].nghbrs[f];
                du[i].nghbrs.erase(du[i].nghbrs.begin() + f);
                du_adjac[i][FE] = 0;
                
                auto it = find (du[FE].Connected.begin(), du[FE].Connected.end(), i);
                
                du[FE].Connected.erase(it);
            }




        /* if (ran2(&iseed) < dlt_nd)                   // chance of delete a connection
            {
                for (int f=0 ; f<du[f].nghbrs.size() ; f++)
                    adjac [i][f] = 0;
                
                for (int f=0 ; f<du[f].Connected.size() ; f++)
                    adjac [f][i] = 0;
            }

            if (ran2(&iseed) < dublict_nd)
            {
                ???
            }
            */
        }
    }

    //saving on the txt file as well:

    if (saving_is_ncessary)
    {
        ofstream sve(du_location);

        for (int i=0 ; i<nn ; i++)
        {
            for (int j=0 ; j<nn ; j++)
            {
                sve<<du_adjac[i][j]<<'\t';
            }

            sve<<'\n';
        }
        sve.close();
    }

    
}