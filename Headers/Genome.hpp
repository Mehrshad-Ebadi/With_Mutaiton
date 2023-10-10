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
#include <ctime>
#include "./Gene.hpp"
#include "./duplicated.hpp"
#include <cstdlib> 

class genome
{
    private:
    int n;
    int nn;
    long int iseed;
    int selected_node;
    vector <int> Alive = {};
    vector <double> ftnss_saver = {};
    double self_regulation_limitation_mean_poisson;

    public:
    int craziness_counter;
    int du_craziness_counter;
    gene* gn;
    dupli* du;
    double** adjac;
    double** du_adjac;
    double positive_chance;
    double xx;
    double XX;
    double Sigma;
    double Miuw;
    double omega;
    double ref_omega;
    double du_omega;
    double du_ref_omega;
    int du_ref_alive;
    int ref_alive;
    int alive;
    int du_alive;
    int population;
    double ref_Envmnt;
    int * output;
    int * input;
    int * du_output;
    int * du_input;
    int II;
    int UU;
    int du_II;
    int du_UU;
    int last_number_got_filled;


 //+++++++++ Mutation update+++++++//

    
 
 //+++++++++ FUNCTIONS+++++++//

    double gasdev(long*);
	double ran2 (long*);
    void base (int); 
    void connect (int, int, double);
    void du_connect (int, int, double);
    bool checker (string);
    bool du_checker (string);
    void Reader(string);
    void du_Reader(string);
    void specefication();
    void du_specefication();
    void duplication ();
    void updater (int);
    void du_updater(int);
    double parameters();
    double du_parameters();

    void memory_Deleter();
    void du_memory_Deleter();
    double The_Function (double);
    
    
    
    double phase()    
    {
        return gn[output[0]].weights;
    }
    double phase2()
    {
        return gn[output[1]].weights;
    }
    double du_phase()    
    {
        return ((du[du_output[0]].weights + du[du_output[0 + UU]].weights) / 2.0);
    }
    double du_phase2()
    {
        return ((du[du_output[1 + UU]].weights + (du[du_output[1]].weights)) / 2.0);
    }

    double Fitness_func(double);

    

//+++++++++ FUNCTIONS_mutation update+++++++//

    void Chance_of_repro(int);
    void Reproduce(int);
    double Self_regulation (); //in the fitness function file
    void Evolution(double);
    void Mutation(string);
    double Environment_changes(int, int);
    //void du_Evolution(double);

        
    genome ()
    {
        Alive.clear();
        ftnss_saver.clear();
    }

};
