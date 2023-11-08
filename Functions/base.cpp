#include "../Headers/Genome.hpp"

void genome::base (int N)
{
    int number_networks = Setting_initial_values(N);
    
    ofstream Alive_counter ("./Outputs/Alive.txt");
    ofstream du_Alive_counter ("./Outputs/du_Alive.txt");
    cout<<"numer"<<number_networks<<endl;
    int needed_networks;
    int du_needed_networks;
    //memorising all networks ....

    for (int i=0 ; i<number_networks; i++)
    {
        temp_net = i;
        string data = "./Results/Net_";
        string du_data = "./Results_du/Net_du_";
        
        string Extension = ".txt";
        string HH = to_string(i);
        
        string location = data + HH + Extension;
        string du_location = du_data + HH + Extension;    
        Reader(location);
        du_Reader(du_location);
    }
    
    int step = 20000;
    for (int ini=1 ; ini < step ; ini+=100)
    {
        cout<<ini<<endl;
        needed_networks = 0;
        du_needed_networks = 0;
        double evolve = 2 * Environment_changes(ini, step) ;
        alive = 0;
        du_alive = 0;
        double KAPA = 0;

        if (ini%100 == 0)
        {
            save(number_networks);
            string py = "python3 ./net_char.py";
            string du_py = "python3 ./du_net_char.py";
            
            system (py.c_str());
            system (du_py.c_str());
        }
        
        for (int pl=0 ; pl < number_networks; pl++)
        {
            
            //cout<<"evol"<<evolve<<endl;
            //cout<<"net="<<pl<<" step = " << ini <<endl;
            

            
            string ancestor_saving = "./Outputs/inheritate.txt";
            string du_ancestor_saving = "./Outputs/du_inheritate.txt";

            temp_net = pl;

            // for single networks ....   
            if (ne[pl].living == true)          //checking if the single network in that location is available ...
            {   
                Mutation();
                Evolution(evolve);
                KAPA = evolve - parameters();
                ne[pl].fitness = Fitness_func(KAPA);
                
                if (ne[pl].fitness > ran2(&iseed))
                {
                    alive ++; 
                }
                
                else 
                {
                    ne[pl].living = false;
                    needed_networks++;
                    memory_Deleter();
                }
            }

            //now the same upper block, but for the duplications
            if (dn[pl].living == true)         //checking if the doubled network in that location is available ...
            {   
                du_Mutation();
                du_Evolution(evolve);
                KAPA = evolve - du_parameters();
                KAPA = Fitness_func(KAPA);
                dn[pl].fitness = KAPA;
                
                if (KAPA > ran2(&iseed))
                {
                    du_alive ++; 
                }
                
                else 
                {
                    dn[pl].living = false;
                    du_needed_networks++;
                    du_memory_Deleter();
                }
                
            }

    
        }

        double zz = static_cast <double> (alive) / number_networks;
        double du_zz = static_cast <double> (du_alive) / number_networks;            
        Alive_counter << evolve <<'\t'<< zz <<endl;
        du_Alive_counter << evolve <<'\t'<< du_zz <<endl;     
            //the whole block is for single networks ...
            //
        if (needed_networks != 0 && alive != 0)
        {
            Chance_of_repro(needed_networks, number_networks);
        }
        
        //now the block of the duplicated network with the same tasks ...
        
        if (du_needed_networks != 0 && du_alive != 0)
        {
            du_Chance_of_repro(du_needed_networks, number_networks);
        }
    }
    cout<<"done!!"<<endl;                 
}
