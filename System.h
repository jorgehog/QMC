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
    virtual double get_wf_val(const Walker &walker) = 0;
    
    
public:
    virtual void initialize_walker(const Walker &walker) = 0;
    

    //This must happen in the solver.
    //virtual double get_spatial_ratio(const Walker &walker_new, int i) = 0;
    
};

class Fermions: public System {
protected:
    
public:
    
    
};

#endif	/* SYSTEM_H */

