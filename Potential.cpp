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
    coulomb_on = Coulomb_on;
    n_p = N_p;
    dim = Dim;
    w = W;
}

double Harmonic_osc::get_pot_E(const Walker& walker) const {
    int i;
    double e_potential;

    e_potential = 0;

    // contribution from oscillator part 
    for (i = 0; i < n_p; i++) {
        e_potential += 0.5 * w * w * walker.get_r_i2(i);
    }

    return e_potential;
}

double Potential::get_Coulomb(const Walker& walker) const {
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