#include "../Headers/Genome.hpp"

int genome::Setting_initial_values(int N)
{
    string rem = "rm ./Outputs/*.txt";
    string hem = "rm ./History/*.txt";
    system (rem.c_str());
    system (hem.c_str());
    ifstream INPUT ("./input/parameters.csv");
    int number_networks;
    double mutation_rate;
    cout<<"before mutaiton"<<endl;
    INPUT >> step >> number_networks >> mutation_rate >> ref_Envmnt;
    
    chance_changing_weight   = mutation_rate;
    chance_of_del_connection = mutation_rate;
    chance_of_new_connetion  = mutation_rate;
    
    Sigma = 0.1;
    Miuw = 0.0;   
    
    n = N;
    nn = 2*n;

    Nedg = 0;
    du_Nedg = 0;
    
    ne = new Net [number_networks];
    dn = new dNet [number_networks];

    for (int i=0 ; i<number_networks ; i++)
    {
        ne[i].gn = new gene [n];
        ne[i].adjac = new double* [n] ;
        ne[i].II = 0;
        ne[i].UU = 0;
        ne[i].living = false;
        ne[i].unique = false;
        ne[i].n_isolate = 0;
        ne[i].n = n;
        ne[i].output = nullptr;
        ne[i].input = nullptr;

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
        dn[i].du_II = 0;
        dn[i].du_UU = 0;
        dn[i].living = false;
        dn[i].unique = false;
        dn[i].n_isolate = 0;
        dn[i].nn = nn;
        dn[i].du_output = nullptr;
        dn[i].du_input = nullptr;

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
    ofstream net_char ("./Outputs/00Net_analysis.txt");
    ofstream du_net_char ("./Outputs/00_du_Net_analysis.txt");
    net_char << "step" <<','<<"net"<<','<<"Mn_ideg"<<","<<"Mn_odeg"<<","<<"cl_c"<<endl;
    du_net_char << "step" <<','<<"net"<<','<<"Mn_ideg"<<","<<"Mn_odeg"<<","<<"cl_c"<<endl;
    return number_networks;
}
