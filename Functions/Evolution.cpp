#include "../Headers/Genome.hpp"


void genome::Evolution(double evolve)
{   
    selected_node = input[0];
    for (int i=0 ; i< n ; i++) gn[i].nm_up = 0;
    cout<<"II"<<II<<endl;
    gn[selected_node].weights = evolve;
    
    
    for (int i=0 ; i<gn[selected_node].nghbrs.size() ; i++)
    {
        cout<<"after for_evo"<<endl;
        int node2 = gn[selected_node].nghbrs[i];
        cout<<"5-here???"<<endl;    
        double VV = 0;   
        
        for (int GH=0 ; GH < gn[node2].Connected.size(); GH++)
        {
            int gh = gn[node2].Connected[GH];
            VV += double(gn[gh].weights * adjac[gh][node2]);
        }
        cout<<"4- here ??"<<endl;
        gn[node2].weights = The_Function(VV);
        updater (node2);
    }

}

void genome::updater (int nodex)
{   
    if (gn[nodex].nm_up < gn[nodex].slf_cntrl)
    {
        cout<<"3-here?"<<endl;
        for (int i=0 ; i<gn[nodex].nghbrs.size() ; i++)
        {   
            cout<< "gn[nodex].nghbrs.size() = "<<gn[nodex].nghbrs.size()<<endl;
            double values = 0;
            int node4 = gn[nodex].nghbrs[i];

            for (int GH=0 ; GH < gn[node4].Connected.size(); GH++)
            {
                cout<<"gn[node4].Connected.size() = "<<gn[node4].Connected.size()<<endl;
                int gh = gn[node4].Connected[GH];
                values += double(gn[gh].weights * adjac[gh][node4]);
            }

            cout<<"after for"<<endl;
            gn[node4].weights = The_Function(values);
            gn[node4].nm_up ++;
            cout<<"1-here?"<<endl;
            updater (node4);
        }
    }
}
