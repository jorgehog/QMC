/* 
 * File:   Coulomb.cpp
 * Author: jorgehog
 * 
 * Created on 20. juni 2012, 15:29
 */

#include "QMCheaders.h"

Coulomb::Coulomb(int n_p, int dim) {
    this->n_p = n_p;
    this->dim = dim;
}

no_Coulomb::no_Coulomb(int n_p, int dim)
: Coulomb(n_p, dim) {

}

full_Coulomb::full_Coulomb(int n_p, int dim)
: Coulomb(n_p, dim) {

}

double full_Coulomb::get_Coulomb(const Walker* walker) const {
    int i, j;
    double e_coulomb;

    e_coulomb = 0;
    for (i = 0; i < n_p - 1; i++) {
        for (j = i + 1; j < n_p; j++) {
            e_coulomb += 1 / walker->r_rel(i,j);
        }
    }

    return e_coulomb;
}


