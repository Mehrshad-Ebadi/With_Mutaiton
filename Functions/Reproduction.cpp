#include "../Headers/Genome.hpp"
#include <iomanip>

void genome::Chance_of_repro(int needed_networks, int Nn)
{
    //ofstream tracking_ancestors (ancestor_saving, ios::app);  //saving ancestors ...
    //tracking_ancestors <<"********************"<<endl;
    //tracking_ancestors <<"step="<<ini<<endl;
    //tracking_ancestors <<"********************"<<endl;
    int sum = 0;    
    //hard and soft selection ...  
    last_number_got_filled = 0;
    
    while (sum < needed_networks)
    {
        int idl_cndt = ran2(&iseed) * Nn;

        if (ne[idl_cndt].living && ne[idl_cndt].fitness > ran2(&iseed))
        {
            //tracking_ancestors <<idl_cndt<<"("<<fitness_idl_cndt<<")"<<"->";
            //tracking_ancestors << offspring<<",";
            
            bool get_copied = true;
            
            while (get_copied)
            {
                int slave = last_number_got_filled;
                if (ne[slave].living == false)
                {
                    Copy(idl_cndt, slave);
                    get_copied = false;
                    sum++;
                }

                last_number_got_filled++;
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

void genome::Copy(int idl, int slv)
{
    ne[slv].living = true;
    
    ne[slv].output = new int [ne[idl].UU];
    
    std::copy(ne[idl].output, ne[idl].output + ne[idl].UU, ne[slv].output);

    ne[slv].input = new int [ne[idl].II];
    std::copy(ne[idl].input, ne[idl].input + ne[idl].II, ne[slv].input);
    ne[slv].unique = false;
    
    for (int F=0 ; F<n ; F++)
    {
        ne[slv].gn[F].dg_in = ne[idl].gn[F].dg_in;
        ne[slv].gn[F].dg_out = ne[idl].gn[F].dg_out;
        
        ne[slv].gn[F].nghbrs = ne[idl].gn[F].nghbrs;
        ne[slv].gn[F].Connected = ne[idl].gn[F].Connected;
        
        ne[slv].gn[F].weights = ne[idl].gn[F].weights;
        ne[slv].gn[F].nm_up = ne[idl].gn[F].nm_up;
    }
    
    for (int h=0 ; h<n ; h++)
    {
        for (int g=0 ; g<n ; g++)
        {
            ne[slv].adjac [h][g] = ne[idl].adjac[h][g];
        }
    }

    ne[slv].II = ne[idl].II;
    ne[slv].UU = ne[idl].UU;
    
}