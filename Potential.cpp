/* 
 * File:   Potential.cpp
 * Author: jorgehog
 * 
 * Created on 13. april 2012, 17:21
 */

#include "Potential.h"
//completed

Potential::Potential(int n_p, int dim, bool coulomb_on) {

    this->n_p = n_p;
    this->dim = dim;


    if (coulomb_on) {
        coulomb = new full_Coulomb(n_p, dim);
    } else {
        coulomb = new no_Coulomb(n_p, dim);
    }
}

Harmonic_osc::Harmonic_osc(int n_p, int dim, double w, bool coulomb_on)
: Potential(n_p, dim, coulomb_on) {

    this->w = w;

}

double Harmonic_osc::get_pot_E(const Walker* walker) const {
    int i;
    double e_potential;

    e_potential = 0;

    // contribution from oscillator part 
    for (i = 0; i < n_p; i++) {
        e_potential += 0.5 * w * w * walker->get_r_i2(i);
    }

    return e_potential + coulomb->get_Coulomb(walker);
}

