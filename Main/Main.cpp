#include "../Headers/Genome.hpp"

int main ()
{
    int N = 20;
    int st = 800;
    int Nn_net = 1000;
    float env_reF[] = {0.5 , 0.2, 0.5, 0.8};
    int envi_func;
    string add;
    string comman;

    string rem = "rm -rf ./Outputs";
    system (rem.c_str());
    comman = "mkdir ./Outputs";
    system (comman.c_str());
    
    //for (int jk=0 ; jk<lineCount ; jk++)
    //{
        //for (int a=0 ; a<4 ; a++)
        //{
            //envi_func = a;
            
            for (int L = 0 ; L < 4 ; L++) 
            {
                float env_ref = env_reF[L];
                float Mute_R = 0.2;
                envi_func = 3;
                int number_runs = 6;
                add = "st_" + to_string(st) + "," + "nn_" + to_string(Nn_net) + "," + "mu_" + to_string(Mute_R) + "," + "ref_env_=" + to_string(env_ref);
                add = "./Outputs/" + add;
                comman = "mkdir " + add;
                system (comman.c_str());
                add = add + "/";
                for (int a=0 ; a<number_runs ; a++)
                {
                    string aDD = "mkdir " + add + "numrun_" + to_string(a);
                    system(aDD.c_str());
                }
                
                for (int RUN = 0; RUN < number_runs; RUN ++) 
                {
                    add = "st_" + to_string(st) + "," + "nn_" + to_string(Nn_net) + "," + "mu_" + to_string(Mute_R) + "," + "ref_env_=" + to_string(env_ref);
                    add = "./Outputs/" + add;
                    add = add + "/";
                    string runFolder = add + "numrun_" + to_string(RUN) + "/";
                    genome GM;
                    GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, envi_func, runFolder);
                }
            }
        //}
    //}
}
