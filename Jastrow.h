/* 
 * File:   Jastrow.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:52
 */

#ifndef JASTROW_H
#define	JASTROW_H

class Jastrow {
protected:
    int n_p;
    int n2;
    int dim;

    virtual double get_deriv(Walker &walker, int i, int k) = 0;


public:
    Jastrow();

    virtual void initialize(const System &system) const = 0;

    virtual double get_val(Walker &walker) = 0;
    virtual double get_j_ratio(Walker &walker_new, Walker &walker_old, int i) = 0;
    //void get_grad(Walker &walker); In walker
    virtual double get_lapl_sum(const Walker &walker) const = 0;

};

class No_Jastrow : public Jastrow {
protected:
     virtual double get_deriv(Walker &walker, int i, int k){return 0;};
    
public:
    No_Jastrow() {};
    
    virtual void initialize(const System &system) const {};

    virtual double get_j_ratio(Wavefunction &wf_new, Wavefunction &wf_old, int i) {return 1;};
    virtual double get_val(Wavefunction &wf){return 1;};
    virtual double get_lapl_sum(const Wavefunction &wf) const {return 0;};
};

class Pade_Jastrow : public Jastrow {
protected:
    double beta;
    double **a;
    
     virtual double get_deriv(Walker &walker, int i, int k);

public:

    Pade_Jastrow(const VMC &vmc, double BETA);

    virtual void initialize(const System &system) const;

    virtual double get_j_ratio(Wavefunction &wf_new, Wavefunction &wf_old, int i);
    virtual double get_val(Wavefunction &wf);
    virtual double get_lapl_sum(const Wavefunction &wf) const;

};

#endif	/* JASTROW_H */

