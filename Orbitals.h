/* 
 * File:   Orbitals.h
 * Author: Jørgen
 *
 * Created on 13. april 2012, 22:33
 */

#ifndef ORBITALS_H
#define	ORBITALS_H

class Walker;
class Orbitals {
protected:
    int n_p;
    int n2;
    int dim;
  
public:
    Orbitals();
    virtual double phi(const Walker &walker, int particle, int q_num) = 0;
    virtual double del_phi(const Walker &walker, int particle, int q_num, int d) = 0;
    virtual double lapl_phi(const Walker &walker, int particle, int q_num) const = 0;

};

class oscillator_basis_HC : private Orbitals {
private:
    double alpha;
    double w;
    
public:
    oscillator_basis_HC(int n_p, int dim, double alpha);
    
    void set_frequency(double w);
    
    virtual double phi(const Walker &walker, int particle, int q_num);
    virtual double del_phi(const Walker &walker, int particle, int q_num, int d);
    virtual double lapl_phi(const Walker &walker, int particle, int q_num) const;
};



#endif	/* ORBITALS_H */

