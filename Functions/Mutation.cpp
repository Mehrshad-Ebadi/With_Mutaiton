#include "../Headers/Genome.hpp"

void genome::Mutation(string location)
{
    double nw_wght  = 0.01;    //new weight
    //double delete_nd   = 0.0003;  // delete a node  
    //double dublict_nd = 0.0002;   //duplicated a node
    double rwrng_nw_cnnctn = 0.01;
    double rwrng_dl_cnnctn = 0.01;
    bool saving_is_ncessary = false;

    for (int i=0 ; i<n-2 ; i++)             
    {
        if (gn[i].nghbrs.size() != 0)
        {
            if (ran2(&iseed) < nw_wght)                 //chance of new weight
            {
                saving_is_ncessary = true;
                
                int f = ran2(&iseed) * gn[i].nghbrs.size();
                f = gn[i].nghbrs[f];

                adjac [i][f] = gasdev(&iseed);
            }

            if (ran2(&iseed) < rwrng_nw_cnnctn)
            {
                saving_is_ncessary = true;
                bool temmpy = true;

                while (temmpy)
                {
                    int f = ran2(&iseed) * n;
                    if (adjac [i][f] == 0)
                    {
                        connect(i, f, gasdev(&iseed));
                        gn[f].Connected.push_back(i);
                        temmpy = false;
                    }                
                }

            }

            if (ran2(&iseed) < rwrng_dl_cnnctn)
            {
                saving_is_ncessary = true;
                int f = ran2(&iseed) * gn[i].nghbrs.size();
                int FE = gn[i].nghbrs[f];
                gn[i].nghbrs.erase(gn[i].nghbrs.begin() + f);
                adjac[i][FE] = 0;
                
                
                auto it = find (gn[FE].Connected.begin(), gn[FE].Connected.end(), i);
                
                gn[FE].Connected.erase(it);
            }




        /* if (ran2(&iseed) < dlt_nd)                   // chance of delete a connection
            {
                for (int f=0 ; f<gn[f].nghbrs.size() ; f++)
                    adjac [i][f] = 0;
                
                for (int f=0 ; f<gn[f].Connected.size() ; f++)
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
        ofstream sve(location);

        for (int i=0 ; i<n ; i++)
        {
            for (int j=0 ; j<n ; j++)
            {
                sve<<adjac[i][j]<<'\t';
            }

            sve<<'\n';
        }
        sve.close();
    }

    
}