#include "../Headers/Genome.hpp"

void genome::base (int N)
{
    int number_networks = 10000;
    n = N;
    gn = new gene [n];
    adjac = new double* [n] ;
    II = 0;
    UU = 0;
    Sigma = 0.1;
    Miuw = 0.0;   
    self_regulation_limitation_mean_poisson = 460.6;
    

    int boz;
    alive = 0;
    du_alive = 0;
    ref_Envmnt = 0.0;  //starting input value, or reference environment value ..
    craziness_counter = 30000; //counting number of cicle in a loop, to check if there is any infinite loops or not.
    du_craziness_counter = 2 * craziness_counter;
    
    for (int i=0 ; i<n ; i++)
    {
        adjac[i] = new double [n];
        gn[i].dg_in = 0;
        gn[i].dg_out = 0;
        gn[i].weights = 0;
        gn[i].slf_cntrl = 0;
    }
   
    iseed = 20L * time(0);

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

    
    
    
    /* Reference conditions :
    **************************************
    **************************************
    **************************************
    */

    ofstream Alive_counter ("./Outputs/Alive.txt");
    ofstream popul ("./Outputs/popul.txt");
    //ofstream du_Alive_counter ("./Outputs/du_Alive.txt");
    //Alive.clear();

    /*
    for (int ini=1 ; ini < 2000000 ; ini++) // the simulation continues running until population of single, duplicates or both reach a small amount (less than 10 networks)
    {
        double evolve = (ini / 1000000.0) + ref_Envmnt; // input (or environment) value
        last_number_got_filled = 0;
        cout<<"step = " << evolve <<endl;
        alive = 0;
        population = 0;
        

        for (int SH=0 ; SH<number_networks ; SH++)
        {
            string data = "./Results/Net_";
            //string du_data = "./Results_du/Net_du_";
            string Extension = ".txt";
            string HH = to_string(SH);
            string location = data + HH + Extension;
            //string du_location = du_data + HH + Extension;       

            if (checker(location) == true) //reading all survived networks from reference environment ...
            {   
                Reader(location);
                Mutation();
                Evolution(evolve);
                double KAPA = evolve - parameters();
                KAPA = Fitness_func(KAPA);
                
                if (KAPA > ran2(&iseed))
                {
                    alive ++; 
                    population ++;
                    Alive.push_back(SH);
                    ftnss_saver.push_back(KAPA);
                }
                
                else 
                {
                    char arr[location.length() + 1]; 
                    strcpy(arr, location.c_str()); 
                    remove(arr);
                }
                
                memory_Deleter();
            }

                     
        }

        cout<<"alive = "<<alive<<endl;
        int needed_networks = number_networks - alive;

        if (alive != number_networks && alive != 0)
        {
            Chance_of_repro(needed_networks);
        }

        else if (alive == 0)
        {
            cout<<"Complete extinsion ..."<<endl;
            break;
        }
        Alive.clear();
        Alive.shrink_to_fit();
        ftnss_saver.clear();
        ftnss_saver.shrink_to_fit();
        
        double zz = static_cast <double> (alive) / number_networks;
        Alive_counter << evolve <<'\t'<< zz <<endl;
        popul << evolve <<'\t'<< population <<endl;
        //du_Alive << evolve <<'\t'<< du_alive <<endl;
    }
    */

    /*
    //WITH NONLINEAR environmental changes
    bool still_alive = true;
    while (still_alive) // the simulation continues running until population of single, duplicates or both reach a small amount (less than 10 networks)
    {
        double mean = 0.009;
        double variance = 0.005;
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<double> distribution(mean, std::sqrt(variance));
        double environmental_changes = distribution(gen);
        double evolve = environmental_changes + ref_Envmnt; // input (or environment) value
        ref_Envmnt += environmental_changes;
        last_number_got_filled = 0;
        cout<<"step = " << evolve <<endl;
        alive = 0;
        population = 0;
        
        for (int SH=0 ; SH<number_networks ; SH++)
        {
            string data = "./Results/Net_";
            //string du_data = "./Results_du/Net_du_";
            string Extension = ".txt";
            string HH = to_string(SH);
            string location = data + HH + Extension;
            //string du_location = du_data + HH + Extension;       

            if (checker(location) == true) //reading all survived networks from reference environment ...
            {   
                Reader(location);
                Mutation();
                Evolution(evolve);
                double KAPA = evolve - parameters();
                KAPA = Fitness_func(KAPA);
                

                if (KAPA > ran2(&iseed))
                {
                    alive ++; 
                    population ++;
                    Alive.push_back(SH);
                    ftnss_saver.push_back(KAPA);
                }
                
                else 
                {
                    char arr[location.length() + 1]; 
                    strcpy(arr, location.c_str()); 
                    remove(arr);
                }
                
                memory_Deleter();
            }

                     
        }

        cout<<"alive = "<<alive<<endl;
        int needed_networks = number_networks - alive;

        if (alive != number_networks && alive != 0)
        {
            Chance_of_repro(needed_networks);
        }

        else if (alive == 0)
        {
            still_alive = false;
            cout<<"Complete extinsion ..."<<endl;
            break;
        }
        Alive.clear();
        Alive.shrink_to_fit();
        ftnss_saver.clear();
        ftnss_saver.shrink_to_fit();

        double zz = static_cast <double> (alive) / number_networks;
        Alive_counter << evolve <<'\t'<< zz <<endl;
        popul << evolve <<'\t'<< population <<endl;
        //du_Alive << evolve <<'\t'<< du_alive <<endl;
    }
    */
    //oscilating environment ...
    
    for (int ini=1 ; ini < 2000000 ; ini++) // the simulation continues running until population of single, duplicates or both reach a small amount (less than 10 networks)
    {
        double rate = 1/2000000.0;
        ref_Envmnt += rate;
        if (ran2(&iseed) < 0.2)
            ref_Envmnt += (0.0001 + (gasdev(&iseed) / 1000.0));

        last_number_got_filled = 0;
        cout<<"step = " << ref_Envmnt <<endl;
        alive = 0;
        population = 0;
        

        for (int SH=0 ; SH<number_networks ; SH++)
        {
            string data = "./Results/Net_";
            //string du_data = "./Results_du/Net_du_";
            string Extension = ".txt";
            string HH = to_string(SH);
            string location = data + HH + Extension;
            //string du_location = du_data + HH + Extension;       

            if (checker(location) == true) //reading all survived networks from reference environment ...
            {   
                Reader(location);
                Mutation();
                Evolution(ref_Envmnt);
                double KAPA = ref_Envmnt - parameters();
                KAPA = Fitness_func(KAPA);
                
                if (KAPA > ran2(&iseed))
                {
                    alive ++; 
                    population ++;
                    Alive.push_back(SH);
                    ftnss_saver.push_back(KAPA);
                }
                
                else 
                {
                    char arr[location.length() + 1]; 
                    strcpy(arr, location.c_str()); 
                    remove(arr);
                }
                
                memory_Deleter();
            }
                     
        }

        cout<<"alive = "<<alive<<endl;
        int needed_networks = number_networks - alive;
        
        if (alive != number_networks && alive != 0)
        {
            Chance_of_repro(needed_networks);
        }

        else if (alive == 0)
        {
            cout<<"Complete extinsion ..."<<endl;
            break;
        }
        Alive.clear();
        Alive.shrink_to_fit();
        ftnss_saver.clear();
        ftnss_saver.shrink_to_fit();
        
        double zz = static_cast <double> (alive) / number_networks;
        Alive_counter << ref_Envmnt <<'\t'<< zz <<endl;
        popul << ref_Envmnt <<'\t'<< population <<endl;
        //du_Alive << evolve <<'\t'<< du_alive <<endl;
    }

    cout<<"done!!"<<endl;                 
}
