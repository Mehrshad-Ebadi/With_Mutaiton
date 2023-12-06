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
    int st;
    int Nn_net;
    float Mute_R, per_iso;
    double  env_ref;
    int envi_func;
    lineCount = lineCount / 6;

    for (int PAR=0; PAR < lineCount ; PAR++)
    {
        Predifined >> st >> Nn_net >> Mute_R >> env_ref >> per_iso >> envi_func;
        genome GM;
        GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, per_iso, envi_func);
    }

}
