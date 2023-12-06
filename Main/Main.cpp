#include "../Headers/Genome.hpp"

int main ()
{
    int N = 20;
    int st;
    int Nn_net;
    double Mute_R, env_ref, per_iso;
    ifstream Predifined ("./input/parameters.csv");

    for (int PAR=0; PAR < 50 ; PAR++)
    {
        Predifined >> st >> Nn_net >> Mute_R >> env_ref >> per_iso;
        genome GM;
        GM.base(N);
    }
    


}
