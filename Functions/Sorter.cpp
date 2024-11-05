#include "../Headers/Genome.hpp"

void genome::sorter(int number_of_lost, int du_number_of_lost)
{
    

    for (int i=0 ; i<last_nu_network; i++)
    {
        int j = i+1;
    
        while (ne[i].living ==false && j < last_nu_network)
        {
            
            if (ne[j].living == true && j < last_nu_network)
            {
                Copy(j, i);
                memory_Deleter(j);
                ne[i].unique = true;
            }   

            else 
                j++;
        }

    }
    
    
    for (int i=0 ; i<du_last_nu_network ; i++)
    {
        int j = i+1;

        while (dn[i].living ==false && j < du_last_nu_network)
        {

            if (dn[j].living == true)
            {
                du_Copy(j, i);
                du_memory_Deleter(j);
                dn[i].unique = true;
            }   

            else 
                j++;
        }
    }

    last_nu_network = last_nu_network - number_of_lost;
    du_last_nu_network = du_last_nu_network - du_number_of_lost;
}
