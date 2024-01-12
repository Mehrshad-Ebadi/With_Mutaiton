#include "../Headers/Genome.hpp"
#include <mpi.h>

int main (int argc, char **argv)
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
    int st = 10000;
    int Nn_net = 10000;
    
    
    lineCount = 1;
    float env_reF[] = {0.0 , 0.2, 0.5, 0.8};

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
            
            int world_size, world_rank;
            MPI_Init(&argc, &argv);
            MPI_Comm_size(MPI_COMM_WORLD, &world_size);
            MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
            
            for (int L = 0 ; L < 4 ; L++) 
            {
                float env_ref = env_reF[L];
                float Mute_R = 0.0001;
                envi_func = 0;
                int number_runs = 10;
                
                if (world_rank == 0) 
                {
                    // Assuming env_reF is available here...
                    string rem = "rm -r ./Outputs/*";
                    system (rem.c_str());
                }
                
                MPI_Barrier(MPI_COMM_WORLD);

                for (int RUN = world_rank; RUN < number_runs; RUN += world_size) 
                {
                    genome GM;
                    GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, envi_func, RUN);
                }
                
                MPI_Barrier(MPI_COMM_WORLD);
                
                if (world_rank == 0)
                {
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
                
            }
            MPI_Finalize();
        //}
    //}
}
