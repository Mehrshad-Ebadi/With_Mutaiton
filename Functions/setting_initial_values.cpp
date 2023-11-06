#include "../Headers/Genome.hpp"

int genome::Setting_initial_values(int N)
{
    int number_networks = 100;
    
    chance_changing_weight = 0.01;
    chance_of_del_connection = 0.01;
    chance_of_new_connetion = 0.01;
    
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
        ne[i].living = false;

        for (int z=0 ; z<n ; z++)
        {
            ne[i].adjac[z] = new double [n];
            ne[i].gn[z].dg_in = 0;
            ne[i].gn[z].dg_out = 0;
            ne[i].gn[z].weights = 0;
            ne[i].gn[z].slf_cntrl = 0;
            ne[i].n = n;
        }

        dn[i].du = new dupli [nn];
        dn[i].du_adjac = new double* [nn];
        dn[i].du_II = 0;
        dn[i].du_UU = 0;
        dn[i].living = false;

        for (int z=0 ; z<nn ; z++)
        {
            dn[i].du_adjac [z] = new double [nn];
            dn[i].du[z].dg_in = 0;
            dn[i].du[z].dg_out = 0;    
            dn[i].du[z].weights = 0;    
            dn[i].du[z].slf_cntrl = 0;
            dn[i].nn = nn;
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
    
    ref_Envmnt = 0.0;  //starting input value, or reference environment value ..
    iseed = 20L * time(0);

    
    ofstream net_char ("./Outputs/00Net_analysis.txt");
    ofstream du_net_char ("./Outputs/00_du_Net_analysis.txt");
    net_char << "step" <<','<<"net"<<','<<"average_in_degree"<<","<<"average_out_degree"<<","<<"diameter"<<","<<"cluster_coeffcient"<<endl;
    du_net_char << "step" <<','<<"net"<<','<<"average_in_degree"<<","<<"average_out_degree"<<","<<"diameter"<<","<<"cluster_coeffcient"<<endl;
    return number_networks;
}