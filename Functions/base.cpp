#include "../Headers/Genome.hpp"

void genome::base (int Nu_n, string add)
{
    int number_networks = Nu_n;
    //string run = "numrun_" + to_string(RUN);
    //add = add + run;
    //add = add + "/";

    ofstream Alive_counter (add + "Alive.txt");
    ofstream du_Alive_counter (add + "du_Alive.txt");
    ofstream enviroment (add + "envi.txt");
    ofstream uni (add + "uni.txt");
    ofstream du_uni (add + "du_uni.txt"); 
    ofstream iso (add + "iso.txt");
    ofstream mutat (add + "num_mutation.txt");
    ofstream du_iso (add + "du_iso.txt");
    int needed_networks;
    int du_needed_networks;
    double evolve = 0;
    ofstream eg(add + "edge.txt");
    ofstream du_eg(add + "du_edge.txt");

    //memorising all networks ....

    for (int i=0 ; i<number_networks; i++)
    {
        string data = "./Population_pool/Results/Net_";
        string du_data = "./Population_pool/Results_du/Net_du_";
        
        string Extension = ".txt";
        string HH = to_string(i);
        
        string location = data + HH + Extension;
        string du_location = du_data + HH + Extension;    
        Reader(location, i);
        du_Reader(du_location, i); 
    }

    vector <int> dead_list;
    vector <int> du_dead_list;
    vector <int> live_list;
    vector <int> du_live_list;
    
    for (int ini=0  ; ini <= (2*step) ; ini++)
    {
        switch (environment_selector)
        {
            case 0 :
                lin_envo = true;
                evolve = Environment_li(ini, step);
                break;
            
            case 1:
                Gaus_envo = true;
                evolve = ref_Envmnt +  Environment_Ga(); //Gaus environment
                break;

            case 2:
                stp_envo = true;
                evolve = Environment_no_l(evolve, step); //No linear with gaus jumps environment
                break;
            
            case 3:
                neg_envo = true;
                evolve = Environment_neg(ini, step); //Negative gradients
                break;

            case 4:
                std_envo = true;
                evolve = ref_Envmnt;
                break;
        }

        if (ini % 400 == 0)
        {
            cout<<"st="<<ini<<endl;
            save(number_networks, ini, add);
        }

        for (int pl=0 ; pl<number_networks ; pl++)
        {
            for (int z=0 ; z<n ; z++)
            {
                ne[pl].gn[z].weights = 0;
                dn[pl].du[z].weights = 0;
                dn[pl].du[z+n].weights = 0;
            }
            
            // for single networks ....   
            if (ne[pl].living == true)          //checking if the single network in that location is available ...
            {   
                Mutation(pl);
                Evolution(evolve, pl);
                double KAPA = evolve - parameters(pl);
                ne[pl].fitness = Fitness_func(KAPA);
                
                if ((ne[pl].fitness >= ran2(&iseed)) && ne[pl].n_isolate < n-2)
                {
                    ne[pl].living = true;
                    fit += ne[pl].fitness; 
                    live_list.push_back(pl);
                }
                
                else 
                {
                    dead_list.push_back(pl);
                    ne[pl].living = false;
                    memory_Deleter(pl);
                }
            }
            
            //now the same upper block, but for the duplications
            if (dn[pl].living == true )         //checking if the doubled network in that location is available ...
            {   
                du_Mutation(pl);
                du_Evolution(evolve, pl);
                double KAPA = evolve - du_parameters(pl);
                KAPA = Fitness_func(KAPA);
                dn[pl].fitness = KAPA;
                
                if ((dn[pl].fitness >= ran2(&iseed))  && dn[pl].n_isolate < nn-2)
                {
                    dn[pl].living == true;
                    du_fit += dn[pl].fitness;
                    du_live_list.push_back(pl);
                }
                
                else 
                {
                    du_dead_list.push_back(pl);
                    dn[pl].living = false;
                    du_memory_Deleter(pl);
                }
            }

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
        
        float total_mutation        = 0.0;
        float du_total_mutation     = 0.0;
        float positive_mutation     = 0.0;
        float du_positive_mutation  = 0.0;

        for (int a=0 ; a<number_networks ; a++)
        {
            total_mutation += ne[a].nm_mutation;
            du_total_mutation += dn[a].nm_mutation;
            
            if (ne[a].living == true)
                positive_mutation += ne[a].nm_mutation;
            
            if (dn[a].living == true)
                du_positive_mutation += dn[a].nm_mutation;
        }
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

        Un = 0;
        du_Un = 0;

        for (int a=0 ; a<live_list.size() ; a++)     
        {
            if (ne[live_list[a]].unique == true)   Un++;
        }

        for (int a=0 ; a<du_live_list.size() ; a++)     
        {
            if (dn[du_live_list[a]].unique == true)   du_Un++;
        }
        //int st=0;
        //for (int i=0 ; i<number_networks; i++)
        //    if (ne[i].living == true)
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
        if (live_list.size() == 0 || du_live_list.size() == 0)
            break;
        iso << ini << '\t' << ((is + 0.0) / number_networks) << endl;
        du_iso << ini << '\t' << ((du_is + 0.0) / number_networks) << endl;
        eg << ini << '\t' << ((E + 0.0) / (number_networks * n))<<endl;
        du_eg << ini << '\t' << ((du_E + 0.0) / ((number_networks)*nn)) <<endl;
        uni << ini << '\t' << Un << endl;
        du_uni << ini << '\t' << du_Un << endl;
        mutat << ini<< '\t' << (positive_mutation/(total_mutation + 0.0))<<'\t'<<(du_positive_mutation/(du_total_mutation + 0.0))<<'\n';
        dead_list.clear();
        dead_list.shrink_to_fit();
        du_dead_list.clear();
        du_dead_list.shrink_to_fit();
        live_list.clear();
        live_list.shrink_to_fit();
        du_live_list.clear();
        du_live_list.shrink_to_fit();
    }

    cout<<'\n'<<"simulation done, wait ..."<<endl;
}
