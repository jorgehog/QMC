/* 
 * File:   Diffusion.cpp
 * Author: jorgehog
 * 
 * Created on 16. april 2012, 14:03
 */

#include <math.h>

#include "Diffusion.h"
#include "Sampling.h"

//METROPOLIS maa ha elsetest som setter blokken med spin motsatt av neste bevegede partikkels spin lik gamle.

Diffusion::Diffusion(int n_p, int dim, double timestep, double random_seed, double D) {
    this->n_p = n_p;
    this->dim = dim;
    this->timestep = timestep;
    this->random_seed = random_seed;
    this->D = D;
    this->std = sqrt(2 * D * timestep);
}

void Diffusion::set_trial_pos(Walker &walker,
        bool load_VMC_dist, std::ifstream* file) {
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

Simple::Simple(int n_p, int dim, double timestep, double random_seed, double D)
: Diffusion(int n_p, int dim, double timestep, double random_seed, double D) {

}

double Simple::get_new_pos(Walker& walker) {
    return gaussian_deviate(&random_seed) * std;
}

double Simple::get_g_ratio(Walker& walker_post, Walker& walker_pre, int particle) {
    return 1;
}














double Fokker_Planck::get_g_ratio(Walker& walker_post, Walker& walker_pre, int particle) {
    
    double g_ratio = 0;
    for (int j = 0; j < dim; j++) {
        g_ratio += 0.5 * (walker_pre.qforce[particle][j] + walker_post.qforce[particle][j])*
                (D * timestep * 0.5 * (walker_pre.qforce[particle][j] - walker_post.qforce[particle][j])
                - walker_post.r[particle][j] + walker_pre.r[particle][j]);
    }

    return exp(g_ratio);
}
