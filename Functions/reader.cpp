#include "../Headers/Genome.hpp"

void genome::Reader(string location)
{

    ifstream NetWork (location);

    for (int j=0 ; j<n ; j++)
    {
        for (int k=0 ; k<n ; k++)
        {
            NetWork>>adjac[j][k];

            if (adjac[j][k] != 0)   connect (j, k, adjac[j][k]);
        }
    }

    specefication();

}

void genome::du_Reader(string du_location)
{
    ifstream NetWork (du_location);

    for (int j=0 ; j<nn ; j++)
    {
        for (int k=0 ; k<nn ; k++)
        {
            NetWork>>du_adjac[j][k];
            
            if (du_adjac[j][k] != 0)    du_connect (j, k, du_adjac[j][k]);
        }
    }
    
    du_specefication();
}