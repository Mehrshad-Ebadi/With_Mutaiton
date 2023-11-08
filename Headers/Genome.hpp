#include <iostream>
#include <fstream>
#include <math.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <limits.h>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>

#include "./DU_net_gene.hpp"
#include "./Net_gene.hpp"

class genome
{
    private:
    int n;
    int nn;
    long int iseed;
    int selected_node;
    
    double chance_changing_weight;
    double chance_of_new_connetion;
    double chance_of_del_connection;


    public:
    //vector <int> du_Alive;
 
    int temp_net;
    //vector <float> du_ftnss_saver;
    Net* ne;
    dNet* dn;
    
    int alive;
    int du_alive;

    double Sigma;
    double Miuw;
    
    double ref_omega;
    
    double du_ref_omega;
    
    int du_ref_alive;
    int ref_alive;

    int du_last_number_got_filled;
    int last_number_got_filled;

    double ref_Envmnt;
    
 //+++++++++ FUNCTIONS+++++++// 
    void base (int);
    int Setting_initial_values(int);

    void Reader(string);
    void du_Reader(string);
    double Self_regulation (); //in the fitness function file
    
    void connect (int, int, double, int);
    void du_connect (int, int, double, int);

    void specefication();
    void du_specefication();

    void Mutation();
    void du_Mutation();

    void Evolution(double);
    void du_Evolution(double);

    void updater (int);
    void du_updater(int);
    
    double parameters();
    double du_parameters();

    double Fitness_func(double);
    
    double The_Function (double);

    void memory_Deleter();
    void du_memory_Deleter();

    void Copy(int, int);
    void du_Copy(int, int);

    void Chance_of_repro(int, int);
    void du_Chance_of_repro(int, int);

    int Reproduce(int);
    int du_Reproduce(int);

    double gasdev(long*);
	double ran2 (long*);    
    void save(int);   

    
    double Environment_changes(int, int);
    //void du_Evolution(double);

    genome()
    {
        
    };
    ~genome() 
    {
    }

};
