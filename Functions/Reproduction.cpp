#include "../Headers/Genome.hpp"
#include <iomanip>

void genome::Reproducing(int total_lost)
{
    int as;
    //cout << "in repro, total lost = "<<total_lost <<'\t';
    //cout<<"we are in the reproduction!"<<endl;

        
    //
    //for (int i=0 ; i<du_last_nu_network ; i++)
    //{
    //    cout<<"before the reproduciton "<<i<<'\t'<<dn[i].fitness<<", living "<<dn[i].living<<'\t'<<dn[i].occ<<'\t'<<du_last_nu_network<<endl;
    //}
//
    //cin >> as; 
    
    for (int i=0 ; i<total_lost ; i++)
    {
        
        int idl_cndt = 0;
        bool duble= false;
        bool single = false;
        bool fitness_passed = true;

        //cout<<"before while:"<<endl;
        
        while (fitness_passed)
        {
            double the_random = ran2(&iseed);
            
            if (ran2(&iseed) >= 0.5)
            {
                idl_cndt = ran2(&iseed) * last_nu_network;

                if (ne[idl_cndt].fitness > the_random )
                {
                    fitness_passed = false;
                    single = true;
                    Copy(idl_cndt, last_nu_network);
                    last_nu_network ++;
                }
            }

            else
            {
                idl_cndt = ran2(&iseed) * du_last_nu_network;

                //cout<< "last = "<<du_last_nu_network <<" idl_cnd = " << idl_cndt << " fitness = " <<dn[idl_cndt].fitness << " the random = " << the_random << endl;
                
                if (dn[idl_cndt].fitness > the_random)
                {
                    //cout<<"idl_cnd = " << idl_cndt << " fitness = " <<dn[idl_cndt].fitness << " the random = " << the_random << endl;
                    
                    //cout<< "idl_cand = "<<idl_cndt<< '\t' << dn[idl_cndt].fitness <<endl;
                    fitness_passed = false;
                    duble = true;
                    du_Copy(idl_cndt, du_last_nu_network);
                    du_last_nu_network ++;  
                }
            }
        }
        
    }

    
//    
//    for (int i=0 ; i<du_last_nu_network ; i++)
//    {
//        cout<<i<<'\t'<<dn[i].fitness<<endl;
//    }
//    cin >> as; 
    //cout << "number_net   " << last_nu_network << '\t' << du_last_nu_network <<endl;
    //cin >> as;
}

void genome::Copy(int idl, int slv)
{
    ne[slv].living = true;
    ne[slv].occ = true;
    ne[slv].fitness = ne[idl].fitness;

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


void genome::du_Copy(int idl, int slv)
{
    dn[slv].living = true;
    dn[slv].occ = true;
    dn[slv].fitness = dn[idl].fitness;
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
}