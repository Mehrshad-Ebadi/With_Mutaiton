#include "../Headers/Genome.hpp"

double genome::parameters (int temp_net)
{
    int s = temp_net;
    ne[s].xx = 0;
    
    for (int i=0 ; i<ne[s].output.size() ; i++) 
    {
        int j = ne[s].output[i];
        ne[s].xx += ne[s].gn[j].weights;
    }

    ne[s].xx = double (ne[s].xx / ne[s].output.size());
    
    return ne[s].xx;
}


double genome::du_parameters (int temp_net)
{
    int s = temp_net;
    dn[s].XX = 0;
    
    for (int i=0 ; i<dn[s].output.size() ; i++) 
    {
        int j = dn[s].output[i];
        dn[s].XX += dn[s].du[j].weights;
    }
    
    dn[s].XX = double (dn[s].XX / dn[s].output.size());
    return dn[s].XX;
}    
