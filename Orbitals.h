/* 
 * File:   Orbitals_old_old.h
 * Author: Jørgen
 *
 * Created on 13. april 2012, 22:33
 */

#ifndef Orbitals_old_H
#define	Orbitals_old_H

class Orbitals_old {
protected:
    int n_p;
    int n2;
    int dim;
  
public:
    Orbitals_old(int n_p, int dim);
    virtual double phi(const Walker* walker, int particle, int q_num) const = 0;
    virtual double del_phi(const Walker* walker, int particle, int q_num, int d) const = 0;
    virtual double lapl_phi(const Walker* walker, int particle, int q_num) const = 0;

};

class oscillator_basis_HC : public Orbitals_old {
private:
    double alpha;
    double w;
    
public:
    oscillator_basis_HC(int n_p, int dim, double alpha, double w = 1.0);
    
    virtual double phi(const Walker* walker, int particle, int q_num) const;
    virtual double del_phi(const Walker* walker, int particle, int q_num, int d) const;
    virtual double lapl_phi(const Walker* walker, int particle, int q_num) const;
};



#endif	/* Orbitals_old_H */

