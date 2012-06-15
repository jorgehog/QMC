/* 
 * File:   System.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:49
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

class Potential;
class Orbitals;
class Walker;

class System {
protected:
    int n_p;
    int dim;
    double a_sym;
    double a_asym;
    
    Potential pot;
    Orbitals orbital;

public:
    System();

    virtual void initialize_for_CF(Walker &walker) = 0;
    virtual void calc_for_newpos(const Walker &walker_old, Walker &walker_new, int particle) = 0;
    virtual double get_spatial_ratio(const Walker &walker, const Walker &walker_old, int i) = 0;
    virtual void update_old(int i) = 0;
    virtual double get_spatial_wf(const Walker &walker) = 0;
    virtual void get_spatial_grad(Walker& walker, int particle) = 0;
    virtual double get_spatial_lapl_sum(const Walker &walker_new, const Walker &walker_old) = 0;

};

class Fermions : public System {
protected:
    int n2;

    double ** s_up;
    double ** s_down;


    void initialize_slaters(const Walker &walker);
    void invert_slaters();
    void make_merged_inv(const Walker &walker);
    void update_inverse(Walker &walker_old, Walker &walker_new, int particle);
    double get_det();

public:
    Fermions(int n_p, int dim, Potential pot, Kinetics kin, Orbitals orbital);

    virtual void initialize_for_CF(Walker &walker);
    virtual void get_spatial_grad(Walker& walker, int particle) = 0;
    virtual void calc_for_newpos(const Walker &walker_old, Walker &walker_new, int i);
    virtual double get_spatial_ratio(const Walker &walker_new, const Walker &walker_old, int i);
    virtual double get_spatial_lapl_sum(const Walker &walker_new, const Walker &walker_old);
    virtual double get_spatial_wf(const Walker& walker);

};


#endif	/* SYSTEM_H */

