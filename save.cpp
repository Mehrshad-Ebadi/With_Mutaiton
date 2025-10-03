#include "../Headers/Genome.hpp"


void genome::save(int nN)
{
    string iden = "./History/Net_";
    string ext = ".txt";
    
    for (int g=0 ; g<nN ; g++)
    {
        string G = to_string(g);
        string saving = iden + G + ext;
        ofstream location (saving); 
        
        for (int i=0; i<n ; i++)
        {
            for (int j=0 ; j<n ; j++)
            {
                location << ne[g].adjac[i][j]<<'\t';
            }

            location << endl;
        }    
    }

    string du_iden = "./History/Net_du_";
    
    for (int g=0 ; g<nN ; g++)
    {
        string G = to_string(g);
        string saving = du_iden + G + ext;
        ofstream location (saving); 
        
        for (int i=0; i<nn ; i++)
        {
            for (int j=0 ; j<nn ; j++)
            {
                location << dn[g].du_adjac[i][j]<<'\t';
            } 

            location << endl;
        }    
    }
}