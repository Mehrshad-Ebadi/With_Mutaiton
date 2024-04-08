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
}

void genome::Copy(int idl, int slv)
{
    ne[slv].living = true;
    
    ne[slv].unique = false;
    ne[slv].output = ne[idl].output;
    ne[slv].input = ne[idl].input;

    ne[slv].unique = false;

    for (int F=0 ; F<n ; F++)
    {
        ne[slv].gn[F].dg_in = ne[idl].gn[F].dg_in;
        ne[slv].gn[F].dg_out = ne[idl].gn[F].dg_out;
        ne[slv].gn[F].slf_cntrl = ne[idl].gn[F].slf_cntrl;
        
        ne[slv].gn[F].nghbrs = ne[idl].gn[F].nghbrs;
        ne[slv].gn[F].Connected = ne[idl].gn[F].Connected;
        
        ne[slv].gn[F].weights = 0;
        ne[slv].gn[F].nm_up = ne[idl].gn[F].nm_up;
        ne[slv].gn[F].isolated = ne[idl].gn[F].isolated;
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
    ne[slv].nm_mutation = ne[idl].nm_mutation;
}