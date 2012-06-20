/* 
 * File:   QMC.cpp
 * Author: jorgehog
 * 
 * Created on 30. mars 2012, 17:42
 */

#include "QMC.h"
#include "System.h"
#include "Jastrow.h"
#include "Diffusion.h"
#include "Kinetics.h"
#include "Walker.h"
#include "Sampling.h"
#include "lib.h"

#include <iostream>

QMC::QMC(int n_p, int dim, int n_c,  Jastrow *jastrow, Sampling *sampling, System *system, Kinetics *kinetics) {
    this->n_p = n_p;
    this->dim = dim;
    this->n_c = n_c;
    this->n2 = n_p / 2;

    this->jastrow = jastrow;
    this->sampling = sampling;
    this->system = system;
    this->kinetics = kinetics;

    this->sampling->set_qmc_ptr(this);
    this->kinetics->set_qmc_ptr(this);

    this->accepted = 0;

}

void QMC::get_gradients(Walker* walker, int particle) {
    jastrow->get_grad(walker);
    system->get_spatial_grad(walker, particle);
}

void QMC::get_gradients(Walker* walker) {
    jastrow->get_grad(walker);
    system->get_spatial_grad(walker, 0);
    system->get_spatial_grad(walker, n2);
}

void QMC::get_wf_value(Walker* walker) {
    walker->value = system->get_spatial_wf(walker) * jastrow->get_val(walker);
}

//void QMC::calc_for_diffused_walker(Walker* walker_prediff, Walker* walker_postdiff, int particle) {
//    system.calc_for_newpos(walker_prediff, walker_postdiff, particle);
//
//    if (kinetics.get_closed_form()) {
//        get_gradients(walker_postdiff, particle);
//        walker_postdiff.lapl_sum = system.get_spatial_lapl_sum(walker_postdiff, walker_prediff) + jastrow.get_lapl_sum(walker_postdiff);
//    } else {
//        get_wf_value(walker_postdiff);
//    }
//}

void QMC::update_pos(Walker* walker_pre, Walker* walker_post, int particle) {
    //OBS: NEED TO RESET OLD VALUES?


    for (int j = 0; j < dim; j++) {
        walker_post->r[particle][j] = walker_pre->r[particle][j]
                + sampling->get_new_pos(walker_pre, particle, j);
    }

    for (int j = 0; j < n_p; j++) {
        if (j != particle) {
            walker_post->r_rel[particle][j] = walker_post->r_rel[j][particle]
                    = walker_post->abs_relative(particle, j);
        }
    }
}

void QMC::update_necessities(Walker* walker_pre, Walker* walker_post, int particle) {
    sampling->update_necessities(walker_pre, walker_post, particle);
}

double QMC::get_acceptance_ratio(Walker* walker_pre, Walker* walker_post, int particle) {
    double spatial = sampling->get_spatial_ratio(walker_post, walker_pre, particle);
    double jast = jastrow->get_j_ratio(walker_post, walker_pre, particle);
    double G = sampling->get_g_ratio(walker_post, walker_pre, particle);

    return spatial * spatial * jast*G;
}

void QMC::calculate_energy_necessities(Walker* walker) {
    sampling->calculate_energy_necessities(walker);
}

void update_walker(Walker* walker_pre, Walker* walker_post, int particle) {
    //TODO
}

bool QMC::metropolis_test(double A) {
    double r = sampling->call_RNG();

    if (r <= A) {
        accepted++;
        return true;

    } else {
        return false;
    }
}

void QMC::update_walker(Walker* walker_pre, Walker* walker_post, int particle){
    sampling->update_walker(walker_pre, walker_post, particle);
}

void QMC::copy_walker(Walker* parent, Walker* child){
    for (int i = 0; i < n_p; i++){
        for (int j = 0; j < dim; j++){
            child->r[i][j] = parent->r[i][j];
        }
        
        for (int k = i + 1; k < n_p - 1; k++){
            child->r_rel[i][k] = child->r_rel[k][i] = parent->r_rel[i][k];
        }
    }
    
    sampling->copy_walker(parent, child);
    
    
}

VMC::VMC(int n_p, int dim, int n_c,  Jastrow *jastrow, Sampling *sampling, System *system, Kinetics *kinetics, bool dist_to_file)
: QMC(n_p, dim, n_c,  jastrow, sampling, system, kinetics) {

    vmc_E = 0;
    E2 = 0;
    
    wfold = new Walker(n_p, dim);
    wfnew = new Walker(n_p, dim);
    
    this->dist_to_file = dist_to_file;
}

void VMC::initialize() {
    jastrow->initialize();
    sampling->set_trial_pos(wfold);
    sampling->get_necessities(wfold);
    copy_walker(wfold, wfnew);
}

void VMC::calculate_energy(Walker* walker) {
    double local_E;
    
    local_E = kinetics->get_KE(walker);
    local_E += system->get_potential_energy(walker);
    vmc_E += local_E;
    E2 += local_E*local_E;

}

void VMC::scale_values(){
    vmc_E/=n_c;
    E2/=n_c;
}

void VMC::run_method() {

    initialize();

    for (int cycle = 0; cycle < n_c; cycle++) {
        for (int particle = 0; particle < n_p; particle++) {
            update_pos(wfold, wfnew, particle);
            update_necessities(wfold, wfnew, particle);

            double A = get_acceptance_ratio(wfold, wfnew, particle);

            if (metropolis_test(A)) {
                update_walker(wfold, wfnew, particle);
            } else {
                //reset_walker(wf_old) NEED TO RESET SOMETHING IF SWITCH SPIN?
            }
        }

        calculate_energy_necessities(wfold);
        calculate_energy(wfold);

    }

    scale_values();

}

void VMC::output(){
    std::cout << "VMC energy: " << vmc_E << std::endl;
    std::cout << "VMC variance: " << E2 << std::endl;
}

