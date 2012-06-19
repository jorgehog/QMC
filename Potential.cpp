/* 
 * File:   Potential.cpp
 * Author: jorgehog
 * 
 * Created on 13. april 2012, 17:21
 */

#include "Potential.h"
//completed

Potential::Potential(){
    
}

Harmonic_osc::Harmonic_osc(int N_p, int Dim, double W, bool Coulomb_on = true){
    
    n_p = N_p;
    dim = Dim;
    w = W;
    
    if (Coulomb_on) {
        coulomb = new full_Coulomb(n_p, dim);
    } else {
        coulomb = new no_Coulomb(n_p, dim);
    }
}

double Harmonic_osc::get_pot_E(const Walker& walker) const {
    int i;
    double e_potential;

    e_potential = 0;

    // contribution from oscillator part 
    for (i = 0; i < n_p; i++) {
        e_potential += 0.5 * w * w * walker.get_r_i2(i);
    }

    return e_potential + coulomb->get_Coulomb(walker);
}

Coulomb::Coulomb(int n_p, int dim){
    this->n_p = n_p;
    this->dim = dim;
}

no_Coulomb::no_Coulomb(int n_p, int dim){
    
}

full_Coulomb::full_Coulomb(int n_p, int dim)
: Coulomb(n_p, dim) {
    
}

double full_Coulomb::get_Coulomb(const Walker& walker) const {
    int i, j;
    double e_coulomb;

    e_coulomb = 0;
    for (i = 0; i < n_p - 1; i++) {
        for (j = i + 1; j < n_p; j++) {
            e_coulomb += 1 / walker.r_rel[i][j];
        }
    }

    return e_coulomb;
}

