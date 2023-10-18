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
    
    for (int ini=0 ; step ; ini+=20) // the simulation continues running until population of single, duplicates or both reach a small amount (less than 10 networks)
    {
        if (ini % 100 == 0)
        {
            ofstream temp ("./temp.txt", ios::out | ios::trunc); 
            temp << (static_cast<double>(ini) / step) <<endl;
            string pythonScript = "python3 net_char.py";
            int pythonExitCode = system(pythonScript.c_str());
        }

        double evolve = Environment_changes(ini, step);
        last_number_got_filled = 0;
        cout<<"step = " << evolve <<endl;
        alive = 0;
        population = 0;
        double KAPA = 0;
        string ancestor_saving = "./net_track/inheritate.txt";

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
                     
        }

        int needed_networks = number_networks - alive;
        
        if (alive != number_networks && alive != 0)
        {
            Chance_of_repro(needed_networks, ini, ancestor_saving, number_networks);
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
