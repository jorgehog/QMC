/* 
 * File:   QMC.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 17:42
 */

#ifndef QMC_H
#define	QMC_H

#include "Walker.h"
#include "Sampling.h"
#include "Kinetics.h"
#include "Jastrow.h"

class Jastrow;
class Sampling;
class System;
class Kinetics;

class QMC {
protected:
    int n_c;

    int n_p;
    int n2;
    int dim;

    int accepted;

    Jastrow *jastrow;
    Sampling *sampling;
    System *system;
    Kinetics *kinetics;

    QMC(int n_p, int dim, int n_c, Jastrow *jastrow, Sampling *sampling, System *system, Kinetics *kinetics);



    virtual void initialize() = 0;



    void update_pos(Walker* walker_pre, Walker*walker_post, int particle);
    void update_necessities(Walker* walker_pre, Walker* walker_post, int particle);
    double get_acceptance_ratio(Walker* walker_pre, Walker* walker_post, int particle);

    void calculate_energy_necessities(Walker* walker);

    bool metropolis_test(double A);
    void update_walker(Walker*walker_pre, Walker* walker_post, int particle);
    void reset_walker(Walker* walker_pre, Walker* walker_post, int particle);

    void copy_walker(Walker* parent, Walker* child);

public:
    
    virtual void run_method() = 0;
    virtual void output() = 0;
    
    void get_gradients(Walker* walker, int particle);
    void get_gradients(Walker* walker);
    void get_wf_value(Walker* walker);

    bool get_kinetic_bool() {
        return kinetics->get_closed_form();
    }

    System* get_system_ptr() {
        return system;
    }

    Kinetics* get_kinetics_ptr() {
        return kinetics;
    }
};

class VMC : public QMC {
protected:
    double vmc_E, E2;

    bool dist_to_file;

    virtual void initialize();
    void calculate_energy(Walker* walker);
    void scale_values();

public:

    VMC(int n_p, int dim, int n_c, Jastrow *jastrow, Sampling *sampling,
            System *system, Kinetics *kinetics, bool dist_to_file = false);


    Walker* wfold;
    Walker* wfnew;

    double get_var();
    double get_energy();
    
    virtual void run_method();
    virtual void output();

};

class DMC : public QMC {
protected:

    int n_w_orig;

    virtual void initialize();
    void increase_walker_space();
    void calc_gs_statistics();
    void bury_the_dead();
    void Evolve_walker(int k);

    //void copy_walker(int parent, int child); ASSIGNMENT OPERATOR. NB: CHECK SIZE
    //bool singular(int k); MAKE WALKER METHOD

    //virtual void update_pos(int k) = 0; THIS IS DIFFUSION

    //problem: DMC not equal for IMPORTANCE vs. BF


public:
    DMC();

    Walker **Angry_mob;

    virtual void run_method();

    virtual void output();
};



#endif	/* QMC_H */
