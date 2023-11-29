#include "../Headers/Genome.hpp"
#include <iomanip>

void genome::du_Chance_of_repro(const vector <int> &live_list, const vector <int> &dead_list)
{
    for (int i=0 ; i<dead_list.size(); i++)
    {
        int idl_cndt = ran2(&iseed) * live_list.size();
        idl_cndt = live_list[idl_cndt];
        int slave = dead_list[i];
        du_Copy(idl_cndt, slave);   
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

void genome::du_Copy(int idl, int slv)
{
    dn[slv].living = true;
    
    dn[slv].du_output = new int [dn[idl].du_UU];
    
    std::copy(dn[idl].du_output, dn[idl].du_output + dn[idl].du_UU, dn[slv].du_output);

    dn[slv].du_input = new int [dn[idl].du_II];
    std::copy(dn[idl].du_input, dn[idl].du_input + dn[idl].du_II, dn[slv].du_input);
    dn[slv].unique = false;
    
    for (int F=0 ; F<nn ; F++)
    {
        dn[slv].du[F].dg_in = dn[idl].du[F].dg_in;
        dn[slv].du[F].dg_out = dn[idl].du[F].dg_out;
        
        dn[slv].du[F].nghbrs = dn[idl].du[F].nghbrs;
        dn[slv].du[F].Connected = dn[idl].du[F].Connected;
        
        dn[slv].du[F].weights = dn[idl].du[F].weights;
        dn[slv].du[F].nm_up = dn[idl].du[F].nm_up;
    }
    
    for (int h=0 ; h<nn ; h++)
    {
        for (int g=0 ; g<nn ; g++)
        {
            dn[slv].du_adjac [h][g] = dn[idl].du_adjac[h][g];
        }
    }

    dn[slv].du_II = dn[idl].du_II;
    dn[slv].du_UU = dn[idl].du_UU;
    dn[slv].edges = dn[idl].edges;
    dn[slv].n_isolate = dn[idl].n_isolate;
}