/* 
 * File:   Sampling.cpp
 * Author: jorgehog
 * 
 * Created on 15. juni 2012, 18:44
 */

#include "Sampling.h"

Sampling::Sampling(int n_p, int dim) {
    this->n_p = n_p;
    this->dim = dim;
}

void Sampling::set_trial_pos(Walker* walker, bool load_VMC_dist, std::ifstream* file) {
    int i, j;

    if (load_VMC_dist) {

        double pos;
        for (i = 0; i < n_p; i++) {
            for (j = 0; j < dim; j++) {
                *file >> pos;
                walker->r[i][j] = pos;
            }
        }
    } else {
        for (i = 0; i < n_p; i++) {
            for (j = 0; j < dim; j++) {
                walker->r[i][j] = diffusion->Diffusion::get_new_pos(walker, i, j);
            }
        }
    }

    walker->make_rel_matrix();

    get_necessities(walker);

}

double Sampling::get_new_pos(Walker* walker_pre, int particle, int j) {
    return diffusion->get_new_pos(walker_pre, particle, j);
}

double Sampling::get_g_ratio(Walker* walker_post, Walker* walker_pre, int particle) {
    return diffusion->get_g_ratio(walker_post, walker_pre, particle);
}

void Sampling::update_walker(Walker* walker_pre, Walker* walker_post, int particle) {
    for (int i = 0; i < dim; i++) {
        walker_pre->r[particle][i] = walker_post->r[particle][i];
    }

    for (int i = 0; i < n_p; i++) {
        walker_pre->r_rel[i][particle] = walker_pre->r_rel[particle][i] = walker_post->r_rel[i][particle];
    }
}

Brute_Force::Brute_Force(int n_p, int dim, double timestep, long random_seed, double D) : Sampling(n_p, dim) {
    is_importance = false;
    diffusion = new Simple(n_p, dim, timestep, random_seed, D);
}

void Brute_Force::update_walker(Walker* walker_pre, Walker* walker_post, int particle) {
    this->Sampling::update_walker(walker_pre, walker_post, particle);
    walker_post->value = walker_pre->value;
}

void Brute_Force::get_necessities(Walker* walker) {
    if (qmc->get_kinetic_bool()) {
        qmc->get_system_ptr()->initialize(walker);
        qmc->get_gradients(walker);
    }

    qmc->get_wf_value(walker);
}

void Brute_Force::update_necessities(Walker* walker_pre, Walker* walker_post, int particle) {
    //no necessities
}

void Brute_Force::calculate_energy_necessities(Walker* walker) {
    qmc->get_kinetics_ptr()->calculate_energy_necessities_BF(walker);
}

double Brute_Force::get_spatial_ratio(Walker* walker_post, Walker* walker_pre, int particle) {
    qmc->get_wf_value(walker_post);

    return walker_post->value / walker_pre->value;
}

void Brute_Force::copy_walker(Walker* parent, Walker* child) {
    qmc->get_kinetics_ptr()->copy_walker_BF(parent, child);
}





Importance::Importance(int n_p, int dim, double timestep, long random_seed, double D) : Sampling(n_p, dim) {
    is_importance = true;
    diffusion = new Fokker_Planck(n_p, dim, timestep, random_seed, D);
}

void Importance::calculate_energy_necessities(Walker* walker) {
    //no necessities
}

void Importance::copy_walker(Walker* parent, Walker* child) {
    qmc->get_kinetics_ptr()->copy_walker_IS(parent, child);
}

void Importance::update_necessities(Walker* walker_pre, Walker* walker_post, int particle) {
    qmc->get_kinetics_ptr()->update_necessities_IS(walker_pre, walker_post, particle);
}

void Importance::update_walker(Walker* walker_pre, Walker* walker_post, int particle) {
    this->Sampling::update_walker(walker_pre, walker_post, particle);
    qmc->get_system_ptr()->update_walker(walker_pre, walker_post, particle);
    qmc->get_kinetics_ptr()->update_walker_IS(walker_pre, walker_post, particle);
}

double Importance::get_spatial_ratio(Walker* walker_post, Walker* walker_pre, int particle){
    //NOT IMPLEMENTED
    return 0;
}

void Importance::get_necessities(Walker* walker){
    //NOT IMPLEMENTED
}
