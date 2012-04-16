/* 
 * File:   System.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:49
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

class Potential;
class Jastrow;
class Orbitals;
class Walker;

class System {
protected:
    int n_p;
    int dim;
    double a_sym;
    double a_asym;
    bool coloumb_switch_on;

    Jastrow jastrow;
    Potential pot;
    Orbitals orbital;

    virtual double get_wf_val(Walker &walker) = 0;


public:
    
    virtual void initialize_walker(const Walker &walker) = 0;
    virtual void calc_for_newpos(const Walker &walker_old, Walker &walker_new, int i) = 0;
    virtual double get_spatial_ratio(const Walker &walker, int i) = 0;
    virtual void update_old(int i) = 0;


};

class Fermions : public System {
protected:
    int n2;

    void initialize_slaters(const Walker &walker);
    void invert_slaters();
    void make_merged_inv(const Walker &walker);
    virtual void get_new_grad(const Walker& walker_old, Walker &walker_new, int particle);
    virtual void get_init_grad(Walker &walker);
    double get_det();

public:
    Fermion(int n_p, int dim, Potential pot, Kinetics kin, Orbitals orbital, bool cs);
    
    
    virtual void initialize(Walker &walker);
    virtual void calc_for_newpos(const Walker &walker_old, Walker &walker_new, int i);
    virtual double get_spatial_ratio(const Walker &walker_new, int i);
    virtual double get_lapl_sum(const Walker &walker) const;

};


#endif	/* SYSTEM_H */

