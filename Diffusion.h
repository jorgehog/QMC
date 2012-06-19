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
    Diffusion(int n_p, int dim, double timestep, double random_seed, double D);

    virtual void set_trial_pos(Walker &walker, bool load_VMC_dist = false, std::ifstream* file = NULL);
    virtual double get_new_pos(Walker &walker) = 0;
    virtual void get_new_values() = 0;
    virtual void update_walker() = 0;
    virtual double get_g_ratio(Walker& walker_post, Walker& walker_pre, int particle) = 0;

};

class Fokker_Planck : public Diffusion {
public:
    Fokker_Planck();

    virtual void set_trial_pos();
    virtual double get_new_pos();
    virtual void get_new_values();
    virtual void update_walker();
    virtual double get_g_ratio(Walker& walker_post, Walker& walker_pre, int particle);

protected:
    double test_qforce(Walker &walker);


};

class Simple : public Diffusion {
public:
    Simple(int n_p, int dim, double timestep, double random_seed, double D = 0.5);


    virtual double get_new_pos(Walker &walker);
    virtual void get_new_values();
    virtual void update_walker();
    virtual double get_g_ratio(Walker& walker_post, Walker& walker_pre, int particle);


};
#endif	/* DIFFUSION_H */

