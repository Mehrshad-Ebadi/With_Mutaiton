#include "../Headers/Genome.hpp"
#include <chrono>
#include <random>

double genome::Fitness_func(double KAPA)
{
    double RR =(1 - abs(KAPA)); //the linear performance function ...
    if (RR < 0)
        RR = 0; //to prevent network from reaching negative performance values, performance values less than zero would be zero as well.
    return RR;

    //double RR = (1/(Sigma * 2.5066)) * exp(-(((KAPA - Miuw) * (KAPA - Miuw)) / (2 * Sigma * Sigma)));
    //return RR; 
}


double genome::Self_regulation()
{
    // Given coefficients
    double a = 433.4;
    double b = 0.013;
    double local_max = 497.0;
    double c = 20.7;

    // Generate a uniform random variable between 0 and 1
    double U = ran2(&iseed);

    // Calculate x using the corrected equation
    double x = local_max - (1 / b) * log(1 - U);

    // Calculate y using the given function with coefficients a, b, c, and local_max
    int randomNumber = local_max - log(a * U + c) / b;
    
    if (randomNumber == 0)
        randomNumber = 1;
    
    //randomNumber += 50000;
    randomNumber = 200000;
    return randomNumber;
}