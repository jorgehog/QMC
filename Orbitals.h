/* 
 * File:   Orbitals.h
 * Author: Jørgen
 *
 * Created on 13. april 2012, 22:33
 */

#ifndef ORBITALS_H
#define	ORBITALS_H

//test

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

class qdots : private Orbitals {
private:
    double alpha;
    
public:
    qdots(int n_p, int dim, double ALPHA);
    
    virtual double phi(const Walker &walker, int particle, int q_num) = 0;
    virtual double del_phi(const Walker &walker, int particle, int q_num, int d) = 0;
    virtual double lapl_phi(const Walker &walker, int particle, int q_num) const = 0;
};



#endif	/* ORBITALS_H */

