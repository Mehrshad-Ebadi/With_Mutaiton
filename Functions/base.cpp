#include "../Headers/Genome.hpp"

void genome::base (int N)
{
    int number_networks = Setting_initial_values(N);
    ofstream Alive_counter ("./Outputs/Alive.txt");
    ofstream du_Alive_counter ("./Outputs/du_Alive.txt");
    
    ofstream popul ("./Outputs/popul.txt");
    ofstream du_popul ("./Outputs/du_popul.txt");
    
    int step = 20000;
    
    for (int ini=5000 ; step ; ini+=20) // the simulation continues running until population of single, duplicates or both reach a small amount (less than 10 networks)
    {
        if ((ini % 100) == 0)
        {
            ofstream temp ("./Outputs/temp.txt", ios::out | ios::trunc); 
            temp << (static_cast<double>(ini) / step) <<endl;
            temp << number_networks <<endl;
            
            string pythonScript = "python3 net_char.py";
            int pythonExitCode = system(pythonScript.c_str());

            string du_pythonScript = "python3 du_net_char.py";
            int du_pythonExitCode = system(du_pythonScript.c_str());

        }

        double evolve = Environment_changes(ini, step);
        last_number_got_filled = 0;
        du_last_number_got_filled = 0;

        cout<<"step = " << ini <<endl;
        
        alive = 0;
        du_alive = 0;

        double KAPA = 0;
        string ancestor_saving = "./net_track/inheritate.txt";
        string du_ancestor_saving = "./net_track/du_inheritate.txt";

        for (int SH=0 ; SH<number_networks ; SH++)
        {
            string data = "./Results/Net_";
            string du_data = "./Results_du/Net_du_";
            
            string Extension = ".txt";
            string HH = to_string(SH);
            string location = data + HH + Extension;
            string du_location = du_data + HH + Extension;       

            // for single networks ....    

            if (checker(location) == true)          //checking if the single network in that location is available ...
            {   
                Reader(location);
                Mutation(location);
                Evolution(evolve);
                KAPA = evolve - parameters();
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
            
            //now the same upper block, but for the duplications
            
            if (checker(du_location) == true)         //checking if the doubled network in that location is available ...
            {   
                du_Reader(location);
                du_Mutation(du_location);
                du_Evolution(evolve);
                KAPA = evolve - du_parameters();
                KAPA = Fitness_func(KAPA);
                
                if (KAPA > ran2(&iseed))
                {
                    du_alive ++; 
                    du_population ++;
                    du_Alive.push_back(SH);
                    du_ftnss_saver.push_back(KAPA);
                }
                
                else 
                {
                    char arr[du_location.length() + 1]; 
                    strcpy(arr, du_location.c_str()); 
                    remove(arr);
                }

                du_memory_Deleter();
            }          
        }

        int needed_networks = number_networks - alive;
        int du_needed_networks = number_networks - du_alive;
        
        //the whole block is for single networks ...
        {
            if (alive != number_networks && alive != 0)
            {
                Chance_of_repro(needed_networks, ini, ancestor_saving, number_networks);
            }

            else if (alive == 0)
            {
                break;
            }
        }

        //now the block of the duplicated network with the same tasks ...
        {
            if (du_alive != number_networks && du_alive != 0)
            {
                du_Chance_of_repro(du_needed_networks, ini, du_ancestor_saving, number_networks);
            }

            else if (du_alive == 0)
            {
                break;
            }
        }
        Alive.clear();
        Alive.shrink_to_fit();
        ftnss_saver.clear();
        ftnss_saver.shrink_to_fit();
        
        du_Alive.clear();
        du_Alive.shrink_to_fit();
        du_ftnss_saver.clear();
        du_ftnss_saver.shrink_to_fit();
        
        double zz = static_cast <double> (alive) / number_networks;
        double du_zz = static_cast <double> (du_alive) / number_networks;

        Alive_counter << evolve <<'\t'<< zz <<endl;
        du_Alive_counter << evolve <<'\t'<< du_zz <<endl;

        popul << evolve <<'\t'<< population <<endl;
        du_popul << evolve <<'\t'<< du_population <<endl;
    }
        
    cout<<"done!!"<<endl;                 
}
