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
}

void genome::du_Copy(int idl, int slv)
{
    dn[slv].living = true;

    dn[slv].output = dn[idl].output;
    dn[slv].input = dn[idl].input;    
    dn[slv].unique = false;
    
    for (int F=0 ; F<nn ; F++)
    {
        dn[slv].du[F].dg_in = dn[idl].du[F].dg_in;
        dn[slv].du[F].dg_out = dn[idl].du[F].dg_out;
        
        dn[slv].du[F].nghbrs = dn[idl].du[F].nghbrs;
        dn[slv].du[F].Connected = dn[idl].du[F].Connected;
        dn[slv].du[F].slf_cntrl = dn[idl].du[F].slf_cntrl;
        
        dn[slv].du[F].weights = 0;
        dn[slv].du[F].nm_up = dn[idl].du[F].nm_up;
        dn[slv].du[F].isolated = dn[idl].du[F].isolated;
    }
    
    for (int h=0 ; h<nn ; h++)
    {
        for (int g=0 ; g<nn ; g++)
        {
            dn[slv].du_adjac [h][g] = dn[idl].du_adjac[h][g];
        }
    }

    dn[slv].II = dn[idl].II;
    dn[slv].UU = dn[idl].UU;
    dn[slv].edges = dn[idl].edges;
    dn[slv].n_isolate = dn[idl].n_isolate;
    dn[slv].nm_mutation = dn[idl].nm_mutation;
    dn[slv].fitness = dn[idl].fitness;
}