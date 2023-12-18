#include "../Headers/Genome.hpp"

int main ()
{
    ifstream Predifined ("./input/parameters.csv");
    int N = 20;
    int st;
    int Nn_net;
    float Mute_R, per_iso;
    double  env_ref;
    int envi_func;
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
            
                case 1:
                    env_ref = 0.1;
                
                case 2:
                    env_ref = 0.5;
                
                case 3:
                    env_ref = 1.0;
                
                case 4:
                    env_ref = 1.2;
            }

            st = 10000;
            Nn_net = 1000;
            genome GM;
            GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, envi_func);
        }
    }
}
