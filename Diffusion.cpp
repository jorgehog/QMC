/* 
 * File:   Diffusion.cpp
 * Author: jorgehog
 * 
 * Created on 16. april 2012, 14:03
 */

#include <math.h>

#include "Diffusion.h"

//METROPOLIS maa ha elsetest som setter blokken med spin motsatt av neste bevegede partikkels spin lik gamle.

Diffusion::Diffusion() {

}

Simple::Simple(int n_p, int dim, double timestep, double D) {
    this->n_p = n_p;
    this->dim = dim;
    this->timestep = timestep;
    this->D = D;
    this->std = sqrt(2 * D * timestep);
}

Diffusion::set_trial_pos(Walker &walker, bool load_VMC_dist, std::ifstream* file) {
    int i, j;

    if (load_VMC_dist) {

        double pos;
        for (i = 0; i < n_p; i++) {
            for (j = 0; j < dim; j++) {
                file >> pos;
                walker->r[i][j] = pos;
            }
        }
    } else {
        walker->r[i][j] = get_new_pos();
    }
    
}



