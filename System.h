/* 
 * File:   System.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:49
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#include "Potential.h"
#include "Walker.h"
#include "Orbitals.h"
#include <armadillo>

class System {
protected:
    int n_p;
    int dim;
    double a_sym;
    double a_asym;

    Potential *pot;
    Orbitals *orbital;

public:
    System(int n_p, int dim, Potential* pot, Orbitals* orbital);

    double get_potential_energy(Walker* walker);
    
    virtual void update_walker(Walker* walker_pre, Walker* walker_post, int particle) = 0;
    
    virtual void calc_for_newpos(Walker* walker_old, Walker* walker_new, int particle) = 0;

    virtual double get_spatial_ratio(Walker* walker_pre, Walker* walker_post, int particle) = 0;

    virtual double get_spatial_wf(const Walker* walker) = 0;
    virtual void get_spatial_grad(Walker* walker, int particle) = 0;
    virtual double get_spatial_lapl_sum(const Walker* walker) = 0;
    virtual void initialize(Walker* walker) = 0;

    virtual void copy_walker(Walker* parent, Walker* child) = 0;
    virtual void reset_walker_ISCF(Walker* walker_pre, Walker* walker_post, int particle) = 0;
};

class Fermions : public System {
protected:
    int n2;

    arma::mat s_up;
    arma::mat s_down;

    
    void initialize_slaters(const Walker* walker);
    void invert_slaters();
    void make_merged_inv(Walker* walker);
    void update_inverse(Walker* walker_old, Walker* walker_new, int particle);
    double get_det();

public:
    Fermions(int n_p, int dim, Potential* pot, Orbitals* orbital);

    virtual void initialize(Walker* walker);
    virtual void get_spatial_grad(Walker* walker, int particle);
    virtual void calc_for_newpos(Walker* walker_old, Walker* walker_new, int i);
    void update_walker(Walker* walker_pre, Walker* walker_post, int particle);
    
    virtual double get_spatial_ratio(Walker* walker_post, Walker* walker_pre, int particle);
    virtual double get_spatial_lapl_sum(const Walker* walker);
    virtual double get_spatial_wf(const Walker* walker);
    
    virtual void copy_walker(Walker* parent, Walker* child);
    virtual void reset_walker_ISCF(Walker* walker_pre, Walker* walker_post, int particle);

};


#endif	/* SYSTEM_H */

