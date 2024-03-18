#include "../Headers/Genome.hpp"

void genome::Reader(string location, int temp_net)
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
            }
        }
        ne[temp_net].gn[j].slf_cntrl = Self_regulation();
    }

    NetWork.close();
    specefication(temp_net);
}

void genome::du_Reader(string du_location, int temp_net)
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
            }
        }
        
        if (j < n)
        {
            dn[temp_net].du[j].slf_cntrl = ne[temp_net].gn[j].slf_cntrl;
        }
    }

    NetWork.close();
    du_specefication(temp_net);
}