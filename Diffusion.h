/* 
 * File:   Diffusion.h
 * Author: jorgehog
 *
 * Created on 16. april 2012, 14:03
 */

#ifndef DIFFUSION_H
#define	DIFFUSION_H

#include <fstream>

class Walker;

class Diffusion {
protected:
    int n_p;
    int dim;

    double timestep;
    double D;
    long random_seed;

    double std;


public:
    Diffusion(int n_p, int dim, double timestep, long random_seed, double D);

    virtual double get_new_pos(Walker* walker, int i, int j);
    
    virtual double get_g_ratio(Walker* walker_post, Walker* walker_pre, int particle) = 0;
    
    double call_RNG();
};

class Fokker_Planck : public Diffusion {
public:
    Fokker_Planck(int n_p, int dim, double timestep, long random_seed, double D = 0.5);

    virtual double get_new_pos(Walker* walker, int i, int j);
    virtual double get_g_ratio(Walker* walker_post, Walker* walker_pre, int particle);

protected:
    double test_qforce(Walker* walker);


};

class Simple : public Diffusion {
public:
    Simple(int n_p, int dim, double timestep,long random_seed, double D = 0.5);


    virtual double get_new_pos(Walker* walker, int i, int j);
    virtual double get_g_ratio(Walker* walker_post, Walker* walker_pre, int particle);


};
#endif	/* DIFFUSION_H */

