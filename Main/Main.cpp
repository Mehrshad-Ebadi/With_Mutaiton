#include "../Headers/Genome.hpp"

int main ()
{
    //ifstream file("./input/parameters.csv"); // Replace with your CSV file path
    //string line;
    int lineCount = 0;

    //if (file.is_open()) {
    //    while (getline(file, line))
    //        lineCount++;
//
    //    file.close(); // Always close the file when you're done with it.
    //    cout << "Number of lines in the file: " << lineCount/6 << endl;
    //}

    //ifstream Predifined ("./input/parameters.csv");
    int N = 20;
    int st = 1000;
    int Nn_net = 10000;
    
    
    lineCount = 1;
    float env_reF[] = {0.0 , 0.2, 0.5};

    string comnd = "rm -rf ./ARCHIVE";
    system (comnd.c_str());
    comnd = "mkdir ./ARCHIVE";
    system (comnd.c_str());

    //for (int jk=0 ; jk<lineCount ; jk++)
    //{
        //for (int a=0 ; a<4 ; a++)
        //{
            //envi_func = a;
            int envi_func = 0;
            

            for (int L=0 ; L<3 ; L++)
            {
                float  env_ref = env_reF[L];
                float Mute_R = 0.001;
                envi_func = 0;
                int number_runs = 4;
                string rem = "rm -r ./Outputs/*";
                system (rem.c_str());

                for (int RUN=0 ; RUN < number_runs ; RUN++)
                {   
                    genome GM;
                    GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, envi_func, RUN);
                }
                
                string add = "st_" + to_string(st) + "," + "nn_" + to_string(Nn_net) + "," + "mu_" + to_string(Mute_R) + "," + "ref_env_=" + to_string(env_ref);
                switch (envi_func)
                {
                    case 0:
                    comnd = "mkdir ./ARCHIVE/Linear_input/";
                    system (comnd.c_str());
                    add = "./ARCHIVE/Linear_input/" + add + "/";
                    break;

                    case 1:    
                    comnd = "mkdir ./ARCHIVE/Gaus_input/";
                    system (comnd.c_str());
                    add = "./ARCHIVE/Gaus_input/" + add + "/";
                    break;
                
                    case 2:
                    comnd = "mkdir ./ARCHIVE/Step_input/";
                    system (comnd.c_str());
                    add = "./ARCHIVE/Step_input/" + add + "/";
                    break;

                    case 3:
                    comnd = "mkdir ./ARCHIVE/Negative_input/";
                    system (comnd.c_str());
                    add = "./ARCHIVE/Negative_input/" + add + "/";
                    break;
                }

                comnd = "mkdir " + add;
                system (comnd.c_str());
                
                comnd = "cp -r ./Outputs/ " + add;
                system (comnd.c_str());
            }
        //}
    //}
}
