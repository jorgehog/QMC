/* 
 * File:   Sampling.cpp
 * Author: jorgehog
 * 
 * Created on 15. juni 2012, 18:44
 */

#include "Sampling.h"
#include "Diffusion.h"
#include "Walker.h"
#include "QMC.h"
#include "Kinetics.h"

Sampling::Sampling(int n_p, int dim) {
    this->n_p = n_p;
    this->dim = dim;
}

void Sampling::set_trial_pos(Walker &walker, bool load_VMC_dist, std::ifstream* file) {
    int i, j;

    if (load_VMC_dist) {

        double pos;
        for (i = 0; i < n_p; i++) {
            for (j = 0; j < dim; j++) {
                file >> pos;
                walker.r[i][j] = pos;
            }
        }
    } else {
        walker.r[i][j] = diffusion->get_new_pos();
    }

    walker.make_rel_matrix();

    get_necessities(walker);

}

double Sampling::get_new_pos(Walker& walker_pre){
    return diffusion->get_new_pos(walker_pre);
}

double Sampling::get_g_ratio(Walker& walker_post, Walker& walker_pre, int particle){
    return diffusion->get_g_ratio(Walker& walker_post, Walker& walker_pre, int particle);
}

Brute_Force::Brute_Force(int n_p, int dim, double timestep, double D) : Sampling(int n_p, int dim) {
    is_importance = false;
    diffusion = new Simple(n_p, dim, timestep, D);
}


void Brute_Force::get_necessities(Walker& walker) {
    if (qmc->get_kinetic_bool()) {
        qmc->get_system_ptr()->initialize(walker);
        qmc->get_gradients(walker);
    }

    qmc->get_wf_value(walker);
}

void Brute_Force::update_necessities(Walker& walker_pre, Walker& walker_post, int particle){
    //no necessities
}

void Brute_Force::calculate_energy_necessities(Walker& walker){
    qmc->get_kinetics_ptr()->calculate_energy_necessities_BF(walker)
}

double Brute_Force::get_spatial_ratio(Walker& walker_post, Walker& walker_pre, int particle){
    qmc->get_wf_value(walker_post);
    
    return walker_post.value/walker_pre.value;
}


Importance::Importance(int n_p, int dim, double timestep, double D) : Sampling(int n_p, int dim) {
    is_importance = true;
    diffusion = new Fokker_Planck(n_p, dim, timestep, D);
}

Importance::calculate_energy_necessities(Walker& walker){
    //no necessities
}

Importance::update_necessities(Walker& walker_pre, Walker& walker_post, int particle){
    qmc->get_kinetics_ptr()->update_necessities_IS(Walker& walker_pre, Walker& walker_post, int particle);
}