#include "../Headers/Genome.hpp"
#include <iomanip>

void genome::Chance_of_repro(const vector <int> &live_list, const vector <int> &dead_list)
{

    for (int i=0 ; i<dead_list.size(); i++)
    {
        int idl_cndt = ran2(&iseed) * live_list.size();
        idl_cndt = live_list[idl_cndt];
        int slave = dead_list[i];
        Copy(idl_cndt, slave);   
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
    ne[slv].edges = ne[idl].edges;
    ne[slv].n_isolate = ne[idl].n_isolate;
}