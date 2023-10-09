#include "../Headers/Genome.hpp"

void genome::duplication()
{

    for (int i=0 ; i<n ; i++)
    {
        for (int j=0 ; j<n ; j++)
        {
            if (adjac [i][j] != 0)
            {
                double Wgh = adjac[i][j];
                du_connect (i, j, Wgh);
                du_connect (i, j+n, Wgh);
                du_connect (i+n, j, Wgh);
                du_connect (i+n, j+n, Wgh);
            }
        }
    }

}