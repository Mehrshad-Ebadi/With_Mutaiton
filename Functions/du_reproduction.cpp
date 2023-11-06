#include "../Headers/Genome.hpp"
#include <iomanip>

void genome::du_Chance_of_repro(int needed_networks, int Nn)
{
    //ofstream tracking_ancestors (ancestor_saving, ios::app);  //saving ancestors ...
    //tracking_ancestors <<"********************"<<endl;
    //tracking_ancestors <<"step="<<ini<<endl;
    //tracking_ancestors <<"********************"<<endl;
    int sum = 0;    
    //hard and soft selection ...  
    
    while (sum < needed_networks)
    {
        int idl_cndt = ran2(&iseed) * Nn;

        if (dn[idl_cndt].living && dn[idl_cndt].fitness > ran2(&iseed))
        {
            //tracking_ancestors <<idl_cndt<<"("<<fitness_idl_cndt<<")"<<"->";
            //tracking_ancestors << offspring<<",";
            
            bool get_copied = true;
            
            while (get_copied)
            {
                int slave = du_last_number_got_filled;
                if (dn[slave].living == false)
                {
                    du_copy(idl_cndt, slave);
                    get_copied = false;
                    sum++;
                }

                du_last_number_got_filled++;
            }
            
        }
    }
    
    //tracking_ancestors<<endl;
    
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

void genome::du_copy(int idl, int slv)
{
    dn[slv].living = true;
    dn[slv].du_output = dn[idl].du_output;
    dn[slv].du_input = dn[idl].du_input ;
    
    for (int F=0 ; F<n ; F++)
    {
        dn[slv].du[F].dg_in = dn[idl].du[F].dg_in;
        dn[slv].du[F].dg_out = dn[idl].du[F].dg_out;
        dn[slv].du[F].nghbrs = dn[idl].du[F].nghbrs;
        dn[slv].du[F].Connected = dn[idl].du[F].Connected;
        dn[slv].du[F].weights = dn[idl].du[F].weights;
        dn[slv].du[F].nm_up = dn[idl].du[F].nm_up;
    }
    
    dn[slv].du_adjac = dn[idl].du_adjac;    
    dn[slv].du_II = dn[idl].du_II;
    dn[slv].du_UU = dn[idl].du_UU;
    
}