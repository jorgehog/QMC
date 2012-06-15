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

    double std;


public:
    Diffusion();

    virtual void set_trial_pos(Walker &walker, bool load_VMC_dist = false, std::ifstream* file = NULL);
    virtual double get_new_pos() = 0;
    virtual void get_new_values() = 0;
    virtual void update_walker() = 0;
    virtual void get_full_ratio() = 0;

};

class Fokker_Planck : public Diffusion {
public:
    Fokker_Planck();

    virtual void set_trial_pos();
    virtual double get_new_pos();
    virtual void get_new_values();
    virtual void update_walker();
    virtual void get_full_ratio();

protected:
    double test_qforce(Walker &walker);
    double get_g_ratio(const Walker &walker_new, const Walker &walker_old);


};

class Simple : public Diffusion {
public:
    Simple(int n_p, int dim, double timestep, double D = 0.5);


    virtual double get_new_pos();
    virtual void get_new_values();
    virtual void update_walker();
    virtual void get_full_ratio();

};
#endif	/* DIFFUSION_H */

