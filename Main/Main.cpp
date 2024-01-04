#include "../Headers/Genome.hpp"

int main ()
{
    ifstream file("./input/parameters.csv"); // Replace with your CSV file path
    string line;
    int lineCount = 0;

    if (file.is_open()) {
        while (getline(file, line))
            lineCount++;

        file.close(); // Always close the file when you're done with it.
        cout << "Number of lines in the file: " << lineCount/6 << endl;
    }

    ifstream Predifined ("./input/parameters.csv");
    int N = 20;
    int st = 10000;
    int Nn_net = 1000;
    float Mute_R;
    double  env_ref;
    int envi_func;
    

    /*for (int jk=0 ; jk<lineCount ; jk++)
    {
        Predifined >> Mute_R;

        for (int a=0 ; a<4 ; a++)
        {
            envi_func = a;

            for (int s=0 ; s<5 ; s++)
            {
                switch (s)
                {
                    case 0:
                        env_ref = 0;
                        break;
                
                    case 1:
                        env_ref = 0.1;
                        break;

                    case 2:
                        env_ref = 0.5;
                        break;

                    case 3:
                        env_ref = 1.0;
                        break;

                    case 4:
                        env_ref = 1.2;
                        break;
                }
                
                genome GM;
                GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, envi_func);
            }
        }
    }*/

    Mute_R = 0.1;
    envi_func = 2;
    env_ref = 1.0;
    genome GM;
    GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, envi_func);
}