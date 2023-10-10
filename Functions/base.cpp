#include "../Headers/Genome.hpp"

void genome::base (int N)
{
    int number_networks = Setting_initial_values(N);

    ofstream Alive_counter ("./Outputs/Alive.txt");
    ofstream popul ("./Outputs/popul.txt");
    //ofstream du_Alive_counter ("./Outputs/du_Alive.txt");
    //Alive.clear();
    cout<<n<<endl;
    int step = 10000;
    
    for (int ini=1 ; step ; ini++) // the simulation continues running until population of single, duplicates or both reach a small amount (less than 10 networks)
    {
        double evolve = Environment_changes(ini, step);
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
                Mutation(location);
                Evolution(evolve);
                double KAPA = evolve - parameters();
                cout<<KAPA<<endl;
                KAPA = Fitness_func(KAPA);
                cout<<"fitness = "<<KAPA<<endl;
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

        int needed_networks = number_networks - alive;
        
        if (alive != number_networks && alive != 0)
        {
            Chance_of_repro(needed_networks);
        }

        else if (alive == 0)
        {
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
    
    cout<<"done!!"<<endl;                 
}
