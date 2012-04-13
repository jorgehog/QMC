/* 
 * File:   System.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:49
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

class System {
protected:
    int n_p;
    int dim;
    double a_sym;
    double a_asym;
    double s_ratio;
    
    virtual double phi(const Wavefunction &wf, int particle, int q_num) = 0;
    virtual double del_phi(const Wavefunction &wf, int particle, int q_num, int d) = 0;
    virtual double lapl_phi(const Wavefunction &wf, int particle, int q_num) const = 0;
    
public:

    double** s_up;
    double** s_down;

    //This must happen in the solver.
    //virtual double get_spatial_ratio(const Wavefunction &wf_new, int i) = 0;
    
};

#endif	/* SYSTEM_H */

