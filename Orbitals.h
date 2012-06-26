/* 
 * File:   Orbitals.h
 * Author: Jørgen
 *
 * Created on 13. april 2012, 22:33
 */

#ifndef ORBITALS_H
#define	ORBITALS_H

class Orbitals {
protected:
    int n_p;
    int n2;
    int dim;
  
public:
    Orbitals(int n_p, int dim);
    virtual double phi(const Walker* walker, int particle, int q_num) const = 0;
    virtual double del_phi(const Walker* walker, int particle, int q_num, int d) const = 0;
    virtual double lapl_phi(const Walker* walker, int particle, int q_num) const = 0;

};

class oscillator_basis_HC : public Orbitals {
private:
    double alpha;
    double w;
    
public:
    oscillator_basis_HC(int n_p, int dim, double alpha, double w = 1.0);
    
    //void set_frequency(double w);
    
    virtual double phi(const Walker* walker, int particle, int q_num) const;
    virtual double del_phi(const Walker* walker, int particle, int q_num, int d) const;
    virtual double lapl_phi(const Walker* walker, int particle, int q_num) const;
};



#endif	/* ORBITALS_H */

