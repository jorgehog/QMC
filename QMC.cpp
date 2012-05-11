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

QMC::QMC() {
}


void QMC::get_gradients(Walker& walker, int particle) {
    jastrow.get_grad(walker);
    system.get_spatial_grad(walker, particle);
}

void QMC::get_gradients(Walker& walker) {
    jastrow.get_grad(walker);
    system.get_spatial_grad(walker, 0);
    system.get_spatial_grad(walker, n2);
}


void QMC::get_wf_value(Walker& walker) {
    walker.value = system.get_spatial_wf(walker) * jastrow.get_val(walker);
}

void QMC::calc_for_diffused_walker(Walker& walker_prediff, Walker& walker_postdiff, int particle){
    system.calc_for_newpos(walker_prediff, walker_postdiff, particle);
    
    if (kinetics.closed_form) {
        get_gradients(walker_postdiff, particle);
        walker_postdiff.lapl_sum = system.get_spatial_lapl_sum(walker_postdiff, walker_prediff) + jastrow.get_lapl_sum(walker_postdiff);
    } else {
        get_wf_value(walker_postdiff);
    }
}



VMC::VMC(int n_p, int dim, int n_c, long random_seed, Jastrow jastrow, Diffusion diffusion, System system, Kinetics kinetics){
    this->n_p = n_p;
    this->dim = dim;
    this->n_c = n_c;
    this->random_seed = random_seed;
    this->n2 = n_p/2;
    this->jastrow = jastrow;
    this->diffusion = diffusion;
    this->system = system;
    this->kinetics = kinetics;
    this->dist_to_file = false;
}

void VMC::run_method(){
    int cycle, i;
    
    initialize();
    
    for (cycle = 0; cycle < n_c; cycle++){
        
        
    }
}

void VMC::initialize(){
    jastrow.initialize();
    diffusion.set_trial_pos() ///stuck: IMPLEMENT DIFFUSIONCPP
}
