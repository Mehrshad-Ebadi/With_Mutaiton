#include "../Headers/Genome.hpp"

void genome::Reader(string location)
{
    
    ifstream NetWork (location);

    for (int j=0 ; j<n ; j++)
    {
        for (int k=0 ; k<n ; k++)
        {
            NetWork>>ne[temp_net].adjac[j][k];

            if (ne[temp_net].adjac[j][k] != 0)   
            {
                connect (j, k, ne[temp_net].adjac[j][k], temp_net);
                Nedg++ ;
            }
        }
    }

    ne[temp_net].unique = true;
    NetWork.close();
    ne[temp_net].living = true;
    specefication(temp_net);

}

void genome::du_Reader(string du_location)
{
    ifstream NetWork (du_location);

    for (int j=0 ; j<nn ; j++)
    {
        for (int k=0 ; k<nn ; k++)
        {
            NetWork>>dn[temp_net].du_adjac[j][k];
            
            if (dn[temp_net].du_adjac[j][k] != 0)    
            {
                du_connect (j, k, dn[temp_net].du_adjac[j][k], temp_net);
                du_Nedg++ ;
            }
        }
    }

    dn[temp_net].unique = true;
    NetWork.close();
    dn[temp_net].living = true;
    du_specefication(temp_net);
}