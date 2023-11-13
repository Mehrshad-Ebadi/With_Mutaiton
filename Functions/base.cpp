#include "../Headers/Genome.hpp"

void genome::base (int N)
{
    int number_networks = Setting_initial_values(N);
    
    ofstream Alive_counter ("./Outputs/Alive.txt");
    ofstream du_Alive_counter ("./Outputs/du_Alive.txt");
    ofstream enviroment ("./Outputs/envi.txt");
    int needed_networks;
    int du_needed_networks;
    double evolve = 0;
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
    
    int step = 10000;
    
    for (int ini=1 ; ini < (2*step) ; ini++)
    {
        needed_networks = 0;
        du_needed_networks = 0;
        //evolve = Environment_li(ini, step) ; //for linear and step based increase
        //evolve = Environment_Ga(); //Gaus environment
        evolve = Environment_no_l(evolve, step); //No linear with gaus jumps environment
        alive = 0;
        du_alive = 0;
        fit = 0;
        du_fit = 0;
        double KAPA = 0;

        /*if (ini%200 == 0)
        {
            cout<<ini<<endl;
            ofstream temp ("./Outputs/temp.txt", ios::out | ios::trunc); 
            temp << evolve <<endl;
            temp << number_networks <<endl;
            
            save(number_networks);
            
            string py = "python3 ./net_char.py";
            string du_py = "python3 ./du_net_char.py";
            
            system (py.c_str());
            system (du_py.c_str());
        }*/
        
        for (int pl=0 ; pl < number_networks ; pl++)
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
                
                if (ne[pl].fitness >= ran2(&iseed))
                {
                    alive ++;
                    fit += ne[pl].fitness; 
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
                
                if (dn[pl].fitness >= ran2(&iseed))
                {
                    du_alive ++; 
                    du_fit += dn[pl].fitness;
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

        Alive_counter << ini <<'\t'<< zz <<endl;
        du_Alive_counter << ini <<'\t'<< du_zz <<endl;
        enviroment << ini <<'\t'<< evolve <<endl;     
        
        //the whole block is for single networks ...
        
        if (needed_networks != 0 && alive != 0)
        {
            Chance_of_repro(needed_networks, number_networks);
        }
        
        //now the block of the duplicated network with the same tasks ...
        
        if (du_needed_networks != 0 && du_alive != 0)
        {
            du_Chance_of_repro(du_needed_networks, number_networks);
        }

        if (alive == 0 || du_alive == 0)
            break;
    }

    cout<<"done!!"<<endl;
}
