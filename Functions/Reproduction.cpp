#include "../Headers/Genome.hpp"

void genome::Chance_of_repro(int needed_networks)
{
    int sum = 0;    
    //hard and soft selection ...  
    
    while (sum < needed_networks)
    {
        int idl_cndt = ran2(&iseed) * Alive.size();
        double fitness_idl_cndt = ftnss_saver[idl_cndt];
        idl_cndt = Alive[idl_cndt];
        if (fitness_idl_cndt > ran2(&iseed))
        {    
            Reproduce(idl_cndt);
            population ++;
            sum++;
        }
    }
    
/*   only hard selection
    while (sum < alive)
    {
        int idl_cndt = ran2(&iseed) * Alive.size();
        idl_cndt = Alive[idl_cndt];
        
        if (ran2(&iseed) > 0.5)
        {    
            Reproduce(idl_cndt);
            population ++;
            sum++;
        }
    }

*/
}


void genome::Reproduce(int idl_nt)
{
    int p = 0;
    string data = "./Results/Net_";
    string Extension = ".txt";
    string SS = to_string(idl_nt);
    string source = data + SS + Extension;

    while (p == 0)
    {
        string DD = to_string(last_number_got_filled);
        string dest = data + DD + Extension;
        
        
        if (checker(dest) == false)
        {
            string command = "cp " + source + " " + dest;
            system(command.c_str());
            p++;
        }

        last_number_got_filled ++ ;

    }
}