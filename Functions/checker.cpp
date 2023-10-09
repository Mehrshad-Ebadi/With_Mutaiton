#include "../Headers/Genome.hpp"

bool genome::checker(string Mahal)
{
    ifstream NetWork (Mahal);

    if (NetWork.good())
    {
        NetWork.close();
        return true;
    }
    
    else 
    {
        NetWork.close();
        return false;
    }
}


bool genome::du_checker(string du_mahal)
{

    ifstream NetWork (du_mahal);

    if (NetWork.good())
    {
        return true;
    }
    else 
    {
        return false;
    }
}