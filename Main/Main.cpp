#include "../Headers/Genome.hpp"
#include <mpi.h>

int main (int argc, char **argv)
{
    ifstream input ("./input/data.txt");
    int N, st, Nn_net, env_ref, envi_func;
    float Mute_R;
    int number_runs = 6;

    input >> N >> st >> Nn_net >> envi_func >> Mute_R;
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
        cout<<"run="<<RUN<<'\t'<<"world_rank="<<world_rank<<'\t'<<"world_size="<<world_size<<endl;
        add = "st_" + to_string(st) + "," + "nn_" + to_string(Nn_net) + "," + "mu_" + to_string(Mute_R) + "," + "ref_env_=" + to_string(env_ref);
        add = "./Outputs/" + add;
        add = add + "/";
        string runFolder = add + "numrun_" + to_string(world_rank) + "/";
        genome GM;
        GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, envi_func, runFolder, RUN);
    }
    
    MPI_Finalize();
}
