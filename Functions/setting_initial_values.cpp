#include "../Headers/Genome.hpp"

int genome::Setting_initial_values(int N)
{
    int number_networks = 10000;
    
    chance_changing_weight = 0.001;
    chance_of_del_connection = 0.001;
    chance_of_new_connetion = 0.001;
    
    Sigma = 0.1;
    Miuw = 0.0;   
    
    n = N;
    nn = 2*n;
    
    gn = new gene [n];
    du = new dupli [nn];

    adjac = new double* [n] ;
    du_adjac = new double* [nn];
    
    II = 0;
    UU = 0;
    du_II = 0;
    du_UU = 0;

    ref_Envmnt = 0.0;  //starting input value, or reference environment value ..
    iseed = 20L * time(0);
    
    for (int i=0 ; i<n ; i++)
    {
        adjac[i] = new double [n];
        gn[i].dg_in = 0;
        gn[i].dg_out = 0;
        gn[i].weights = 0;
        gn[i].slf_cntrl = 0;
    }
    
    for (int i=0 ; i<nn ; i++)
    {
        du_adjac [i] = new double [nn];
        du[i].dg_in = 0;
        du[i].dg_out = 0;    
        du[i].weights = 0;    
        du[i].slf_cntrl = 0;
    } 
    

    for (int i=0 ; i<n ; i++)
    {
        for (int j=0 ; j<n ; j++)
            adjac[i][j] = 0;
    }

    for (int i=0 ; i<nn ; i++)
    {    
        for (int j=0 ; j<nn ; j++)
            du_adjac[i][j] = 0;
    }
    
    ofstream net_char ("./Outputs/00Net_analysis.txt");
    ofstream du_net_char ("./Outputs/00_du_Net_analysis.txt");
    net_char << "step" <<','<<"net"<<','<<"average_in_degree"<<","<<"average_out_degree"<<","<<"diameter"<<","<<"cluster_coeffcient"<<endl;
    du_net_char << "step" <<','<<"net"<<','<<"average_in_degree"<<","<<"average_out_degree"<<","<<"diameter"<<","<<"cluster_coeffcient"<<endl;
    
    return number_networks;
}