#include "../Headers/Genome.hpp"


void genome::save(int nN, int ini, string sv_addrs)
{
    string his_addrs = sv_addrs + "History.txt";
    string du_his_addrs = sv_addrs + "History_du.txt";
    
    ofstream location (his_addrs, ios::app);
    ofstream du_location (du_his_addrs, ios::app);
    
    location << "st."<< ini << '\n';
    du_location << "st."<< ini << '\n';

    for (int g=0 ; g<nN ; g++)
    {
        if (ne[g].occ = true)
        {   
            location << ("Network_" + to_string(g)) << '\n';
            du_location << ("Network_" + to_string(g)) << '\n';

            for (int i=0; i<n ; i++)
            {
                for (int j=0 ; j<n ; j++)
                {
                    location << ne[g].adjac[i][j]<<'\t';
                }

                location << endl;
            }

            location << "---" <<'\n';
        }
        
        if (dn[g].occ = true)
        {
            for (int i=0; i<nn ; i++)
            {
                for (int j=0 ; j<nn ; j++)
                {
                    du_location << dn[g].du_adjac[i][j]<<'\t';
                } 

                du_location << endl;
            }

            du_location << "---" << '\n';
        }
    }  
}