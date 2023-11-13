#include "../Headers/Genome.hpp"

double genome::Environment_li(int random_value, int step)
{

    //linear environment:
    double evolve = (static_cast<double>(random_value) / step) + ref_Envmnt ; 
    return evolve;
}

double genome::Environment_Ga()
{
    double mean = 0.1;
    double variance = 0.3;
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(mean, std::sqrt(variance));
    double evolve = distribution(gen);
    return evolve;
}
    

double genome::Environment_no_l(int random_value, int step)
{
    double evolve = (static_cast<double>(random_value) / step) + ref_Envmnt;
    if (ran2(&iseed) > 0.3)
    {
        double mean = 0.0;
        double variance = 0.5;
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<double> distribution(mean, std::sqrt(variance));
        double evolve = distribution(gen) + evolve;
    } 

    return evolve;
}