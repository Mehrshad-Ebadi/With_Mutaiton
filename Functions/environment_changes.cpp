#include "../Headers/Genome.hpp"

double genome::Environment_changes(int random_value, int step)
{

    //linear environment:
    double evolve = (static_cast<double>(random_value) / step) + ref_Envmnt + 0.2; 
    return evolve;

    //Gaussian distribution as environmental changes:
    /*
    double mean = 0.009;
    double variance = 0.005;
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(mean, std::sqrt(variance));
    double evolve = distribution(gen);
    return evolve;
    */

    //oscilating environment :
    /*
    double evolve = (static_cast<double>(random_value) / step) + ref_Envmnt;
    if (ran2(&iseed) > 0.3)
    {
        double mean = 0.0;
        double variance = 0.05;
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<double> distribution(mean, std::sqrt(variance));
        double evolve = distribution(gen) + evolve;
    } 

    return evolve;
    */
}