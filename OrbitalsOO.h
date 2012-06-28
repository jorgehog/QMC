/* 
 * File:   OrbitalsOO.h
 * Author: jorgehog
 *
 * Created on 26. juni 2012, 17:41
 */

#ifndef ORBITALSOO_H
#define	ORBITALSOO_H

class Orbitals {
protected:
    int n_p;
    int n2;
    int dim;

    function** basis_functions;
    function*** dell_basis_functions;
    function** lapl_basis_functions;

public:


    Orbitals(int n_p, int dim);

    virtual double phi(const Walker* walker, int particle, int q_num) const = 0;
    virtual double del_phi(const Walker* walker, int particle, int q_num, int d) const = 0;
    virtual double lapl_phi(const Walker* walker, int particle, int q_num) const = 0;
};

class oscillator_basis : public Orbitals {
private:
    double alpha;
    double w;

public:
    oscillator_basis(int n_p, int dim, double alpha, double w = 1.0);


    virtual double phi(const Walker* walker, int particle, int q_num) const;
    virtual double del_phi(const Walker* walker, int particle, int q_num, int d) const;
    virtual double lapl_phi(const Walker* walker, int particle, int q_num) const;
};

#endif	/* ORBITALSOO_H */

