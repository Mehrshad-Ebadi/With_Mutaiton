#include "../Headers/Genome.hpp"

int genome::Setting_initial_values(int N)
{
    
    n = N;
    gn = new gene [n];
    adjac = new double* [n] ;
    II = 0;
    UU = 0;
    alive = 0;
    du_alive = 0;
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
   
    

    for (int i=0 ; i<n ; i++)
    {
        for (int j=0 ; j<n ; j++)
            adjac[i][j] = 0;
    }

    //+++++++++++++++++++++++++++++++++ the process of duplications++++++++++++++++++++++++++++++++++++++++++
    /*
    nn = 2*n;
    du_adjac = new double* [nn];
    du = new dupli [nn];
    du_II = 0;
    du_UU = 0;
    
    for (int i=0 ; i<nn ; i++)
    {
        du_adjac [i] = new double [nn];
        du[i].dg_in = 0;
        du[i].dg_out = 0;    
        du[i].weights = 0;    
        du[i].slf_cntrl = 0;
    }

    for (int i=0 ; i<nn ; i++)
    {    for (int j=0 ; j<nn ; j++)
            du_adjac[i][j] = 0;
    }

    for (int i=0 ; i<100 ; i++)
    {
        ran2(&iseed);
    }
    */
   int number_networks = 10000;
   return number_networks;
}