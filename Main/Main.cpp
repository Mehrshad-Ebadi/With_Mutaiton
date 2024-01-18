#include "../Headers/Genome.hpp"
#include <mpi.h>

int main (int argc, char **argv)
{
    int N = 20;
    int st = 300;
    int Nn_net = 100;
    float env_reF[] = {0.0 , 0.2, 0.5, 0.8};
    int envi_func = 0;
    string add;
    int world_size, world_rank;
    string comman;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    if (world_rank == 0)
    {
        string rem = "rm -rf ./Outputs";
        system (rem.c_str());
        comman = "mkdir ./Outputs";
        system (comman.c_str());
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    //for (int jk=0 ; jk<lineCount ; jk++)
    //{
        //for (int a=0 ; a<4 ; a++)
        //{
            //envi_func = a;
            
            for (int L = 0 ; L < 4 ; L++) 
            {
                float env_ref = env_reF[L];
                float Mute_R = 0.0001;
                envi_func = 0;
                int number_runs = 6;
                
                if (world_rank == 0) 
                {
                    // Assuming env_reF is available here...
                    
                    
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
                }
                
                MPI_Barrier(MPI_COMM_WORLD);
                
                for (int RUN = world_rank; RUN < number_runs; RUN += world_size) 
                {
                    add = "st_" + to_string(st) + "," + "nn_" + to_string(Nn_net) + "," + "mu_" + to_string(Mute_R) + "," + "ref_env_=" + to_string(env_ref);
                    add = "./Outputs/" + add;
                    add = add + "/";
                    string runFolder = add + "numrun_" + to_string(world_rank) + "/";
                    genome GM;
                    GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, envi_func, runFolder);
                }
                
                MPI_Barrier(MPI_COMM_WORLD);
                
            }
            MPI_Finalize();
        //}
    //}
}
