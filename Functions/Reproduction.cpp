#include "../Headers/Genome.hpp"
#include <iomanip>

void genome::Chance_of_repro(int needed_networks, int Nn)
{
    int sum = 0;    
    last_number_got_filled = 0;
    
    while (sum < needed_networks)
    {
        int idl_cndt = ran2(&iseed) * Nn;

        if (ne[idl_cndt].living && ne[idl_cndt].fitness > ran2(&iseed))
        {
            bool get_copied = true;
            
            while (get_copied)
            {
                int slave = last_number_got_filled;
                if (ne[slave].living == false)
                {
                    copy(idl_cndt, slave);
                    get_copied = false;
                    sum++;
                }

                last_number_got_filled++;
            }
            
        }
    }
    

}

void genome::copy(int idl, int slv)
{
    ne[slv].living = true;
    ne[slv].output = ne[idl].output;
    ne[slv].input = ne[idl].input ;
    
    for (int F=0 ; F<n ; F++)
    {
        ne[slv].gn[F].dg_in = ne[idl].gn[F].dg_in;
        ne[slv].gn[F].dg_out = ne[idl].gn[F].dg_out;
        ne[slv].gn[F].nghbrs = ne[idl].gn[F].nghbrs;
        ne[slv].gn[F].Connected = ne[idl].gn[F].Connected;
        ne[slv].gn[F].weights = ne[idl].gn[F].weights;
        ne[slv].gn[F].nm_up = ne[idl].gn[F].nm_up;
    }
    
    ne[slv].adjac = ne[idl].adjac;    
    ne[slv].II = ne[idl].II;
    ne[slv].UU = ne[idl].UU;
    
}