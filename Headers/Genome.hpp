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
    int selected_node, environment_selector;

    double chance_changing_weight;
    double chance_of_new_connetion;
    double chance_of_del_connection;


    public:
    //vector <int> du_Alive;
    int step;
    //vector <float> du_ftnss_saver;
    Net* ne;
    dNet* dn;
    
    int Nedg;
    int du_Nedg;

    double fit;
    double du_fit;

    double Sigma;
    double Miuw;    

    int du_last_number_got_filled;
    int last_number_got_filled;

    double ref_Envmnt;

    bool lin_envo;
    bool Gaus_envo;
    bool stp_envo;
    bool neg_envo;
    
 //+++++++++ FUNCTIONS+++++++// 
    void base (int);
    void Setting_initial_values(int, int, int, float, double, int);

    void Reader(string, int);
    void du_Reader(string, int);
    double Self_regulation (); //in the fitness function file
    
    void connect (int, int, double, int);
    void du_connect (int, int, double, int);

    void specefication(int);
    void du_specefication(int);

    void Mutation(int);
    void du_Mutation(int);

    void Evolution(double, int);
    void du_Evolution(double, int);

    void updater (int, int);
    void du_updater(int, int);
    
    double parameters(int);
    double du_parameters(int);

    double Fitness_func(double);
    
    double The_Function (double);

    void memory_Deleter(int);
    void du_memory_Deleter(int);

    void Copy(int, int);
    void du_Copy(int, int);

    void Chance_of_repro(const vector <int> &live_list, const vector <int> &dead_list);
    void du_Chance_of_repro(const vector <int> &du_live_list, const vector <int> &du_dead_list);

    int Reproduce(int);
    int du_Reproduce(int);

    double gasdev(long*);
	double ran2 (long*);    
    void save(int, int);   

    
    double Environment_li(int, int);
    double Environment_Ga();
    double Environment_no_l(int, int);
    double Environment_neg(int, int);
    //void du_Evolution(double);

    genome()
    {
        
    };
    ~genome() 
    {
    }

};
