/* 
 * File:   System.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:49
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

class Potential;
class Kinetics;

class System {
protected:
    int n_p;
    int dim;
    double a_sym;
    double a_asym;
    bool coloumb_switch_on;

    Potential pot;
    Kinetics kin;


    virtual double phi(const Walker &walker, int particle, int q_num) = 0;
    virtual double del_phi(const Walker &walker, int particle, int q_num, int d) = 0;
    virtual double lapl_phi(const Walker &walker, int particle, int q_num) const = 0;


    virtual double get_wf_val(Walker &walker) = 0;


public:
    virtual void initialize_walker(const Walker &walker) = 0;
    virtual void calc_for_newpos(const Walker &walker_old, Walker &walker_new, int i) = 0;
    virtual double get_spatial_ratio(const Walker &walker, int i) = 0;
    virtual void update_old(int i) = 0;


    //This must happen in the solver.
    //virtual double get_spatial_ratio(const Walker &walker_new, int i) = 0;

};

class Fermions : public System {
protected:
    int n2;
    
    void initialize_slaters(const Walker &walker);
    void invert_slaters();
    void make_merged_inv(const Walker &walker);
    virtual void get_new_grad(const Walker& walker_old, Walker &walker_new, int particle);
    virtual void get_init_grad(Walker &walker, Jastrow_factor &jastrow);
    double get_det();

public:
    virtual void initialize(Walker &walker);
    virtual void calc_for_newpos(const Walker &walker_old, Walker &walker_new, int i);
    virtual double get_spatial_ratio(const Walker &walker_new, int i);
    virtual double get_lapl_sum(const Walker &walker) const;

};

class qdots : public fermions {
public:
    double alpha;
    double w;

    qdots(int n_p, int dim, const Kinetics *kinetic, const Harmonic_osc *pot, double ALPHA);

    virtual double phi(const Wavefunction &wf, int particle, int q_num);
    virtual double del_phi(const Wavefunction &wf, int particle, int q_num, int d);
    virtual double lapl_phi(const Wavefunction &wf, int particle, int q_num) const;



};

#endif	/* SYSTEM_H */

