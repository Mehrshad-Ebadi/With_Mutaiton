#include "../Headers/Genome.hpp"

void genome::Setting_initial_values(int N, int st, int Nn_net, float Mute_R, float env_ref, int func_env, int RUN)
{
    int number_networks = Nn_net;

    cout<< N << '\t' << st<< '\t'  << Nn_net<< '\t'  << Mute_R<< '\t'  << env_ref<< '\t' << func_env << endl;
    step = st;
    
    chance_changing_weight   = Mute_R;
    chance_of_del_connection = Mute_R;
    chance_of_new_connetion  = Mute_R;
    ref_Envmnt = env_ref;
    environment_selector = func_env;

    lin_envo  = false   ;
    Gaus_envo = false   ;
    stp_envo  = false   ;
    neg_envo  = false   ;
    
    Sigma = 0.1;
    Miuw = 0.0;   
    
    n = N;
    nn = 2*n;
    
    ne = new Net [number_networks];
    dn = new dNet [number_networks];

    for (int i=0 ; i<number_networks ; i++)
    {
        ne[i].gn = new gene [n];
        ne[i].adjac = new double* [n] ;
        ne[i].II = 0;
        ne[i].UU = 0;
        ne[i].living = true;
        ne[i].unique = true;
        ne[i].n_isolate = 0;
        ne[i].n = n;

        for (int z=0 ; z<n ; z++)
        {
            ne[i].adjac[z] = new double [n];
            ne[i].gn[z].dg_in = 0;
            ne[i].gn[z].dg_out = 0;
            ne[i].gn[z].weights = 0;
            ne[i].gn[z].slf_cntrl = 0;
            ne[i].gn[z].isolated = false;
        }

        dn[i].du = new dupli [nn];
        dn[i].du_adjac = new double* [nn];
        dn[i].II = 0;
        dn[i].UU = 0;
        dn[i].living = true;
        dn[i].unique = true;
        dn[i].n_isolate = 0;
        dn[i].nn = nn;

        for (int z=0 ; z<nn ; z++)
        {
            dn[i].du_adjac [z] = new double [nn];
            dn[i].du[z].dg_in = 0;
            dn[i].du[z].dg_out = 0;    
            dn[i].du[z].weights = 0;    
            dn[i].du[z].slf_cntrl = 0;
            dn[i].du[z].isolated = false;
        } 

        for (int z=0 ; z<n ; z++)
        {
            for (int j=0 ; j<n ; j++)
                ne[i].adjac[z][j] = 0;
        }

        for (int z=0 ; z<nn ; z++)
        {
            for (int j=0 ; j<nn ; j++)
                dn[i].du_adjac[z][j] = 0;
        }
    }
    
    iseed = 20L * time(0); 
    base(number_networks, RUN);
}
