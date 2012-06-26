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



    void update_pos(const Walker* walker_pre, Walker*walker_post, int particle) const;
    void update_necessities(const Walker* walker_pre, Walker* walker_post, int particle) const;
    double get_acceptance_ratio(const Walker* walker_pre, const Walker* walker_post, int particle) const;

    void calculate_energy_necessities(Walker* walker) const;

    bool metropolis_test(double A);
    void update_walker(Walker*walker_pre, const Walker* walker_post, int particle) const;
    void reset_walker(const Walker* walker_pre, Walker* walker_post, int particle) const;

    void copy_walker(const Walker* parent, Walker* child) const;

public:
    
    virtual void run_method() = 0;
    virtual void output() const = 0;
    
    void get_gradients(Walker* walker, int particle) const;
    void get_gradients(Walker* walker) const;
    void get_wf_value(Walker* walker) const;
    void get_laplsum(Walker* walker) const;


    System* get_system_ptr() {
        return system;
    }

    Kinetics* get_kinetics_ptr() {
        return kinetics;
    }
    
    Sampling* get_sampling_ptr() {
        return sampling;
    }
    
    Jastrow* get_jastrow_ptr() {
        return jastrow;
    }
};

class VMC : public QMC {
protected:
    double vmc_E, E2;

    bool dist_to_file;

    virtual void initialize();
    void calculate_energy(const Walker* walker);
    void scale_values();

public:

    VMC(int n_p, int dim, int n_c, Jastrow *jastrow, Sampling *sampling,
            System *system, Kinetics *kinetics, bool dist_to_file = false);


    Walker* wfold;
    Walker* wfnew;

    double get_var() const;
    double get_energy() const;
    
    virtual void run_method();
    virtual void output() const;

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
