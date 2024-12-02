#include "../Headers/Genome.hpp"

double genome::Environment_li(int inii)
{

    //linear environment:
    double evolve = (static_cast<double>(inii * len_step)) + first_input ;
    return evolve;
}

double genome::Environment_Ga()
{
    double evolve = 2.0;
    while (abs(evolve) > 1.9)
    {
        double variance = 0.5;
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<double> distribution(mean_input, std::sqrt(variance));
        evolve = distribution(gen);
    }
    return evolve;
}


double genome::Environment_uniform()
{
    double evolve = 2.0;
    while (abs (evolve) > 1.9)
    {
        evolve = first_input + ((last_input - first_input) * ran2(&iseed));

    }

    return evolve;
}


double genome::Environment_neg(int inii)
{
    double evolve = first_input + (static_cast<double>(inii * len_step));
    return evolve;
}
~       
