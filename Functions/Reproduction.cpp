#include "../Headers/Genome.hpp"
#include <iomanip>

void genome::Chance_of_repro(int needed_networks, int ini, string ancestor_saving, int number_networks)
{
    ofstream tracking_ancestors (ancestor_saving, ios::app);  //saving ancestors ...
    tracking_ancestors <<"********************"<<endl;
    tracking_ancestors <<"step="<<ini<<endl;
    tracking_ancestors <<"********************"<<endl;
    int sum = 0;    
    //hard and soft selection ...  
    
    while (sum < needed_networks)
    {
        int idl_cndt = ran2(&iseed) * Alive.size();
        double fitness_idl_cndt = ftnss_saver[idl_cndt];
        idl_cndt = Alive[idl_cndt];
        fitness_idl_cndt = round(fitness_idl_cndt *100) / 100.0;
        
        if (fitness_idl_cndt > ran2(&iseed))
        {   
            tracking_ancestors <<idl_cndt<<"("<<fitness_idl_cndt<<")"<<"->";
            int offspring = Reproduce(idl_cndt, ancestor_saving);
            tracking_ancestors << offspring<<",";
            population ++;
            sum++;
        }
        
        
    }
    
    tracking_ancestors<<endl;
    
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


int genome::Reproduce(int idl_nt, string ancestor_saving)
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
            string offspring = "Net_" + DD;
            string command = "cp " + source + " " + dest;
            system(command.c_str());
            p++;
        }

        last_number_got_filled ++ ;

    }
    return (last_number_got_filled - 1);
}