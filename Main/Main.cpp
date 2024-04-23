#include "../Headers/Genome.hpp"
#include <mpi.h>

int main (int argc, char **argv)
{
    ifstream input ("./input/data.txt");
    int N, st, Nn_net, env_ref, envi_func;
    float Mute_R;
    int number_runs = 6;
    double starting_input;
    double last_input;

    input >> N >> st >> Nn_net >> envi_func >> Mute_R >> starting_input >> last_input;
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

        add = "st" + to_string(st) + "_" + "nn" + to_string(Nn_net) + "_" + "mu" + to_string(Mute_R) + 
        "_" + "refenv" + to_string(env_ref) + "_" + "strt_inpt" + to_string(starting_input);
        
        add = "mkdir ./Outputs/" + add;
        
        system (add.c_str());
        add = add + "/";
        
        for (int a=0 ; a<number_runs ; a++)
        {
            string aDD = add + "numrun_" + to_string(a);
            system(aDD.c_str());
        }
    }
    
    add =  "st" + to_string(st) + "_" + "nn" + to_string(Nn_net) + "_" + "mu" + to_string(Mute_R) + 
        "_" + "refenv" + to_string(env_ref) + "_" + "strt_inpt" + to_string(starting_input) + "/";
    add = "./Outputs/" + add + "/";
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    for (int RUN = world_rank; RUN < number_runs; RUN += world_size) 
    {
        string runFolder = add + "numrun_" + to_string(world_rank) + "/";
        genome GM;
        GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, envi_func, runFolder, RUN, starting_input, last_input);
    }
    
    MPI_Finalize();
}
