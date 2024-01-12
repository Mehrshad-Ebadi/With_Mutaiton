#include "../Headers/Genome.hpp"

int main ()
{
    string rem = "rm -r ./Outputs/*";
    string hem = "rm ./History/*.txt";
    system (rem.c_str());
    system (hem.c_str());
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
    int number_runs = 4;
    for (int RUN=0 ; RUN < number_runs ; RUN++)
    {
        Mute_R = 0.01;
        envi_func = 0;
        env_ref = 0.0;
        genome GM;
        GM.Setting_initial_values(N, st, Nn_net, Mute_R, env_ref, envi_func, RUN);
    }

    string comnd = "mkdir ./ARCHIVE";
    system (comnd.c_str());
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

    comnd = "cp -r ./History/ " + add;
    system (comnd.c_str());
    
    comnd = "cp -r ./Outputs/ " + add;
    system (comnd.c_str());
    
    //comnd = "python3 plotter.py ";
    //system (comnd.c_str());
    
    //comnd = "cp -r ./diagrams/ " + add;
    //system (comnd.c_str());
    
    cout << "Results are copied to the directory of "<<"'"<<add<<"' successfully!"<<"\a"<<endl;
}
