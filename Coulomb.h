/* 
 * File:   Coulomb.h
 * Author: jorgehog
 *
 * Created on 20. juni 2012, 15:29
 */

#ifndef COULOMB_H
#define	COULOMB_H

#include "Walker.h"

class Coulomb {
public:
    int n_p;
    int dim;

    Coulomb(int n_p, int dim);
    virtual double get_Coulomb(const Walker* walker) const = 0;

};

class no_Coulomb : public Coulomb {
public:
    no_Coulomb(int n_p, int dim);

    double get_Coulomb(const Walker* walker) const {
        return 0;
    }


};

class full_Coulomb : public Coulomb {
public:
    full_Coulomb(int n_p, int dim);

    double get_Coulomb(const Walker* walker) const;
};

#endif	/* COULOMB_H */

