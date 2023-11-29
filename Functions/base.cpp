#include "../Headers/Genome.hpp"

void genome::base (int N)
{
    int number_networks = Setting_initial_values(N);
    ofstream Alive_counter ("./Outputs/Alive.txt");
    ofstream du_Alive_counter ("./Outputs/du_Alive.txt");
    ofstream enviroment ("./Outputs/envi.txt");
    ofstream uni ("./Outputs/uni.txt");
    ofstream du_uni ("./Outputs/du_uni.txt"); 
    int needed_networks;
    int du_needed_networks;
    double evolve = 0;
    int net_saver_counter = 0;
    ofstream eg("./Outputs/edge.txt");
    ofstream du_eg("./Outputs/du_edge.txt");

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
    
    Nedg = Nedg / number_networks;
    du_Nedg = du_Nedg / number_networks;
    min_isolated_percent = 10;
    du_min_isolated_percent = 20;
    //du_Nedg ;
    //Nedg;
    //cout << Nedg << '\t' << du_Nedg << endl;

    for (int ini=0  ; ini < (2*step) ; ini++)
    {
        needed_networks = 0;
        du_needed_networks = 0;
        
        vector <int> dead_list;
        vector <int> du_dead_list;
        vector <int> live_list;
        vector <int> du_live_list;
        
        evolve = Environment_li(ini, step) ; //for linear and step based increase
        //evolve = Environment_Ga(); //Gaus environment
        //evolve = Environment_no_l(evolve, step); //No linear with gaus jumps environment
        //evolve = Environment_neg(ini, step); //Negative gradients
        alive = 0;
        du_alive = 0;
        fit = 0;
        du_fit = 0;
        double KAPA = 0;

        if (ini % 200 == 0 && ini > 6800)
        {
            cout<<"saving st="<<ini<<endl;
            ofstream temp ("./Outputs/temp.txt", ios::out | ios::trunc); 
            temp << evolve <<endl;
            temp << number_networks <<endl;
            save(number_networks, ini);
            cout<<"Written!"<<endl;
        }
        
        for (int pl=0 ; pl < number_networks ; pl++)
        {
            //cout<<"evol"<<evolve<<endl;
            //cout<<"net="<<pl<<" step = " << ini <<endl;
                    if (ini % 200 == 0 && ini > 6800)
        {
            cout<<"II="<<ne[pl].II<<" UU="<<ne[pl].UU<<endl;}
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

                if ((ne[pl].fitness >= ran2(&iseed)) && ne[pl].n_isolate < min_isolated_percent)
                {
                    alive ++;
                    fit += ne[pl].fitness; 
                    live_list.push_back(pl);
                }
                
                else 
                {
                    needed_networks++;
                    ne[pl].living = false;
                    memory_Deleter();
                    dead_list.push_back(pl);
                }
            }

            //now the same upper block, but for the duplications
            if (dn[pl].living == true )         //checking if the doubled network in that location is available ...
            {   
                du_Mutation();
                du_Evolution(evolve);
                KAPA = evolve - du_parameters();
                KAPA = Fitness_func(KAPA);
                dn[pl].fitness = KAPA;
                
                if ((dn[pl].fitness >= ran2(&iseed)) && dn[pl].n_isolate < du_min_isolated_percent)
                {
                    du_alive ++;
                    du_fit += dn[pl].fitness;
                    du_live_list.push_back(pl);
                }
                
                else 
                {
                    du_needed_networks++;
                    dn[pl].living = false;
                    du_memory_Deleter();
                    du_dead_list.push_back(pl);
                }
            }
        }

        double zz = static_cast <double> (alive) / number_networks;
        double du_zz = static_cast <double> (du_alive) / number_networks;

        Alive_counter << ini <<'\t'<< zz <<endl;
        du_Alive_counter << ini <<'\t'<< du_zz <<endl;
        enviroment << ini <<'\t'<< evolve <<endl;

        int Un = 0; 
        int du_Un = 0;

        //the whole block is for single networks ...
        
        if (needed_networks != 0 && alive != 0)
        {
            Chance_of_repro(live_list, dead_list);
        }
        
        //now the block of the duplicated network with the same tasks ...
        
        if (du_needed_networks != 0 && du_alive != 0)
        {
            du_Chance_of_repro(du_live_list, du_dead_list);
        }
        
        for (int a=0 ; a<number_networks ; a++)     
        {
            if (ne[a].unique == true)   Un++;
            
            if (dn[a].unique == true)   du_Un++;
        }

        double E=0;
        double du_E =0;
   
        for (int po=0 ; po<number_networks ; po++)
        { 
            E += ne[po].edges;
            du_E += dn[po].edges;
        }

        eg << ini << '\t' << ((E + 0.0) / (number_networks * n))<<endl;
        du_eg << ini << '\t' << ((du_E + 0.0) / ((number_networks)*nn)) <<endl;
        uni << ini << '\t' << Un << endl;
        du_uni << ini << '\t' << du_Un << endl;

        if (alive == 0 || du_alive == 0)
            break;
    }

    cout<<"done!!"<<endl;
}
