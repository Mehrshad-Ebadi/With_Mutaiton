#include "../Headers/Genome.hpp"

double genome::Environment_li(int random_value, int step)
{

    //linear environment:
    double evolve = (static_cast<double>(random_value) / step) + ref_Envmnt ; 
    return evolve;
}

double genome::Environment_Ga()
{
    double mean = 0.0;
    double variance = 0.25;
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(mean, std::sqrt(variance));
    double evolve = distribution(gen);
    return evolve;
}
    

double genome::Environment_no_l(int random_value, int step)
{
    double mean = 0.05;
    double variance = 0.1;
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(mean, std::sqrt(variance));
    double evolve = distribution(gen) + random_value;
    return evolve;
}


double genome::Environment_neg(int random_value, int step)
{
    double evolve = ref_Envmnt  - (static_cast<double>(random_value) / step); 
    return evolve;
}