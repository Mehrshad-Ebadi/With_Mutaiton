#include "../Headers/Genome.hpp"

void genome::base (int Nu_n, string add)
{
    int number_networks = Nu_n * 2;
    //string run = "numrun_" + to_string(RUN);
    //add = add + run;
    //add = add + "/";
    ofstream Alive_counter (add + "Alive.txt");
    ofstream du_Alive_counter (add + "du_Alive.txt");
    ofstream enviroment (add + "envi.txt");
    ofstream iso (add + "iso.txt");
    ofstream du_iso (add + "du_iso.txt");
    int needed_networks;
    int du_needed_networks;
    double evolve = 0;
    ofstream eg(add + "edge.txt");
    ofstream du_eg(add + "du_edge.txt");
    
    last_nu_network = population;
    du_last_nu_network = population;

    //memorising all networks ....

    for (int i=0 ; i<population; i++)
    {
        string data = "../Population_pool/Results/Net_";
        string du_data = "../Population_pool/Results_du/Net_du_";
        
        string Extension = ".txt";
        string HH = to_string(i);
        
        string location = data + HH + Extension;
        string du_location = du_data + HH + Extension;    
        Reader(location, i);
        du_Reader(du_location, i); 
    }
    
    int lost_networks = 0;
    int du_lost_networks = 0;

    for (int ini=0  ; ini <= step ; ini++)
    {
        switch (environment_selector)
        {
            case 0 :
                lin_envo = true;
                evolve = Environment_li(ini);
                break;
            
            case 1:
                Gaus_envo = true;
                evolve = ref_Envmnt +  Environment_Ga(); //Gaus environment
                break;

            case 2:
                uni_envo = true;
                evolve = Environment_uniform(); //No linear with gaus jumps environment
                break;
            
            case 3:
                neg_envo = true;
                evolve = Environment_neg(ini); //Negative gradients
                break;

            case 4:
                std_envo = true;
                evolve = mean_input;
                break;
        } 

        if (ini % 30 == 0)
        {
            cout<<"st="<<ini<<endl;
            //save(number_networks, ini, add);
        }

        int iterator_range = 0;
        lost_networks = 0;
        du_lost_networks = 0;

        if (last_nu_network >= du_last_nu_network)
        iterator_range = last_nu_network;

        else iterator_range = du_last_nu_network;

        for (int pl=0 ; pl<2* population ; pl++)
        {
            if (ne[pl].occ == true)
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
                        ne[pl].occ = true;
                        fit += ne[pl].fitness;
                    }
                    
                    else 
                    {   
                        lost_networks++;
                        ne[pl].living = false;
                        ne[pl].occ = false;
                        memory_Deleter(pl);
                    }
                }
            }

            if (dn[pl].occ == true)   
            { 
                for (int z=0 ; z<n ; z++)
                {
                    dn[pl].du[z].weights = 0;
                    dn[pl].du[z+n].weights = 0;
                }
                //now the same upper block, but for the duplications
                if (dn[pl].living == true)         //checking if the doubled network in that location is available ...
                {   
                    du_Mutation(pl);
                    du_Evolution(evolve, pl);
                    double KAPA = evolve - du_parameters(pl);
                    KAPA = Fitness_func(KAPA);
                    dn[pl].fitness = KAPA;
                    //cout<<dn[pl].fitness<<endl;
                    
                    if ((dn[pl].fitness >= ran2(&iseed))  && dn[pl].n_isolate < nn-2)
                    {
                        dn[pl].living == true;
                        du_fit += dn[pl].fitness;
                        dn[pl].occ = true;
                    }
                    
                    else 
                    {   
                        du_lost_networks ++;
                        dn[pl].living = false;
                        du_memory_Deleter(pl);
                        dn[pl].occ = false;
                    }
                }
            }
        }


        //int st=0;
        //for (int i=0 ; i<number_networks; i++)
        //    if (dn[i].living == true)
        //        st++;
        //cout<<"before copy="<<st<<endl;

        //filling empty spot by sorting and not reproducing:

        sorter(lost_networks, du_lost_networks);

        Alive_counter << ini <<'\t'<< last_nu_network <<endl;
        du_Alive_counter << ini <<'\t'<< du_last_nu_network <<endl;
        enviroment << ini <<'\t'<< evolve <<endl;

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
        int five_percent = population / 20;

        //if (last_nu_network <= (five_percent) || du_last_nu_network <= five_percent )
        //    break;


        //Reproducing GRNs

        int total_lost = lost_networks + du_lost_networks;
        //cout <<"before repro, " << "du_last= "<<du_last_nu_network << '\t' << last_nu_network<<endl; 
        /*cout << "number of removed networks" << totoal_lost << endl;
        {
            for (int i =0 ; i<du_last_nu_network ; i++)
                cout<<i<<'\t'<<dn[i].fitness << endl;

            int sa;
        cin>>sa;
        }
        */
        if (total_lost != 0 && total_lost<population*2 && (last_nu_network != 0 || du_last_nu_network != 0 ))
        {
            //cout<< "are we in the reproduction process?"<<" input = "<< evolve<<endl;
            Reproducing(total_lost);
        }

        //if (du_last_nu_network > 914)

        
        //now the block of the duplicated network with the same tasks ...
        
        
        //final check:: 
        
    }

    cout<<'\n'<<"simulation done, wait ..."<<endl;
}
