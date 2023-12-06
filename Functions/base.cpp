#include "../Headers/Genome.hpp"

void genome::base (int Nu_n)
{
    int number_networks = Nu_n;
    ofstream Alive_counter ("./Outputs/Alive.txt");
    ofstream du_Alive_counter ("./Outputs/du_Alive.txt");
    ofstream enviroment ("./Outputs/envi.txt");
    ofstream uni ("./Outputs/uni.txt");
    ofstream du_uni ("./Outputs/du_uni.txt"); 
    ofstream iso ("./Outputs/iso.txt");
    ofstream du_iso ("./Outputs/du_iso.txt");
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
        string data = "./Population_pool/Results/Net_";
        string du_data = "./Population_pool/Results_du/Net_du_";
        
        string Extension = ".txt";
        string HH = to_string(i);
        
        string location = data + HH + Extension;
        string du_location = du_data + HH + Extension;    
        Reader(location);
        du_Reader(du_location);
        
    }

    Nedg = Nedg / number_networks;
    du_Nedg = du_Nedg / number_networks;
    int du_min_isolated_percent = max_isolated * nn;
    int min_isolated_percent = max_isolated * n;

    vector <int> dead_list;
    vector <int> du_dead_list;
    vector <int> live_list;
    vector <int> du_live_list;
    
    for (int ini=0  ; ini < (4*step) ; ini++)
    {
        switch (environment_selector)
        {
            case 0 :
                lin_envo = true;
                evolve = Environment_li(ini, step);
                break;
            
            case 1:
                Gaus_envo = true;
                evolve = Environment_Ga(); //Gaus environment
                break;

            case 2:
                stp_envo = true;
                evolve = Environment_no_l(evolve, step); //No linear with gaus jumps environment
                break;
            
            case 3:
                neg_envo = true;
                evolve = Environment_neg(ini, step); //Negative gradients
                break;
        }

        fit = 0;
        du_fit = 0;
        double KAPA = 0;
    

        if (ini % 200 == 0)
        {
            cout<<"st="<<ini<<endl;
            ofstream temp ("./Outputs/temp.txt", ios::out | ios::trunc); 
            temp << evolve <<endl;
            temp << number_networks <<endl;
            save(number_networks, ini);
        }
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

                if ((ne[pl].fitness >= ran2(&iseed)) && ne[pl].n_isolate < min_isolated_percent)
                {
                    ne[pl].living = true;
                    fit += ne[pl].fitness; 
                    live_list.push_back(pl);
                }
                
                else 
                {
                    dead_list.push_back(pl);
                    ne[pl].living = false;
                    memory_Deleter();
                }
            }
            
            //else dead_list.push_back(pl);

            //now the same upper block, but for the duplications
            if (dn[pl].living == true )         //checking if the doubled network in that location is available ...
            {   
                du_Mutation();
                du_Evolution(evolve);
                KAPA = evolve - du_parameters();
                KAPA = Fitness_func(KAPA);
                dn[pl].fitness = KAPA;
                
                if ((dn[pl].fitness >= ran2(&iseed))  && dn[pl].n_isolate < du_min_isolated_percent)
                {
                    dn[pl].living == true;
                    du_fit += dn[pl].fitness;
                    du_live_list.push_back(pl);
                }
                
                else 
                {
                    du_dead_list.push_back(pl);
                    dn[pl].living = false;
                    du_memory_Deleter();
                }
            }

            //else du_dead_list.push_back(pl);
            //cout<<dn[pl].n_isolate<<endl;
        }
        //int st=0;
        //for (int i=0 ; i<number_networks; i++)
        //    if (dn[i].living == true)
        //        st++;
        //cout<<"before copy="<<st<<endl;
        double zz = static_cast <double> (live_list.size()) / number_networks;
        double du_zz = static_cast <double> (du_live_list.size()) / number_networks;

        Alive_counter << ini <<'\t'<< zz <<endl;
        du_Alive_counter << ini <<'\t'<< du_zz <<endl;
        enviroment << ini <<'\t'<< evolve <<endl;

        int Un = 0; 
        int du_Un = 0;
        
        //the whole block is for single networks ...
        
        if (dead_list.size() != 0 && live_list.size() != 0)
        {
            Chance_of_repro(live_list, dead_list);
        }
        
        //now the block of the duplicated network with the same tasks ...
        
        if (du_dead_list.size() != 0 && du_live_list.size() != 0)
        {
            du_Chance_of_repro(du_live_list, du_dead_list);
        }

        for (int a=0 ; a<number_networks ; a++)     
        {
            if (ne[a].unique == true)   Un++;
            
            if (dn[a].unique == true)   du_Un++;
        }
        //st=0;
        //for (int i=0 ; i<number_networks; i++)
        //    if (dn[i].living == true)
        //        st++;
        //cout<<"after copy = "<<st<<endl;
        double E=0;
        double du_E =0;
   
        for (int po=0 ; po<number_networks ; po++)
        { 
            E += ne[po].edges;
            du_E += dn[po].edges;
        }

        int is = 0;
        int du_is =0;

        for (int po=0 ; po<number_networks ; po++)
        { 
            is += ne[po].n_isolate;
            du_is += dn[po].n_isolate;
        } 

        iso << ini << '\t' << ((is + 0.0) / number_networks) << endl;
        du_iso << ini << '\t' << ((du_is + 0.0) / number_networks) << endl;
        eg << ini << '\t' << ((E + 0.0) / (number_networks * n))<<endl;
        du_eg << ini << '\t' << ((du_E + 0.0) / ((number_networks)*nn)) <<endl;
        uni << ini << '\t' << Un << endl;
        du_uni << ini << '\t' << du_Un << endl;

        if (live_list.size() == 0 || du_live_list.size() == 0)
            break;

        dead_list.clear();
        du_dead_list.clear();
        live_list.clear();
        du_live_list.clear();

    }

    cout<<'\n'<<"simulation done, wait ..."<<endl;
    string comnd = "mkdir ./ARCHIVE";
    system (comnd.c_str());
    string add = "st_" + to_string(step) + "," + "nn_" + to_string(number_networks) + "," + "mu_" + to_string(chance_of_new_connetion) + "," + "ref_env_=" + to_string(ref_Envmnt) + "," + "Max_iso_si=" + to_string(max_isolated);
    
    if (lin_envo)
    {
        comnd = "mkdir ./ARCHIVE/Linear_input/";
        system (comnd.c_str());
        add = "./ARCHIVE/Linear_input/" + add + "/";
    }

    if (Gaus_envo)
    {
        comnd = "mkdir ./ARCHIVE/Gaus_input/";
        system (comnd.c_str());
        add = "./ARCHIVE/Gaus_input/" + add + "/";
    }

    if (stp_envo)
    {
        comnd = "mkdir ./ARCHIVE/Step_input/";
        system (comnd.c_str());
        add = "./ARCHIVE/Step_input/" + add + "/";
    }

    if (neg_envo)
    {
        comnd = "mkdir ./ARCHIVE/Negative_input/";
        system (comnd.c_str());
        add = "./ARCHIVE/Negative_input/" + add + "/";
    }

    
    
    comnd = "mkdir " + add;
    system (comnd.c_str());

    comnd = "cp -r ./History/ " + add;
    system (comnd.c_str());
    
    comnd = "cp -r ./Outputs/ " + add;
    system (comnd.c_str());
    
    comnd = "python3 plotter.py ";
    system (comnd.c_str());
    
    comnd = "cp -r ./diagrams/ " + add;
    system (comnd.c_str());
    
    cout << "Results are copied to the directory of "<<"'"<<add<<"' successfully!"<<endl;
}
