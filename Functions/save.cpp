#include "../Headers/Genome.hpp"


void genome::save(int nN, int ini)
{
    ofstream location ("./History/Network.txt", ios::app);
    ofstream du_location ("./History/du_Network.txt", ios::app);
    location << "st."<< ini << '\n';
    du_location << "st."<< ini << '\n';

    for (int g=0 ; g<nN ; g++)
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