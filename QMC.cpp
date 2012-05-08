/* 
 * File:   QMC.cpp
 * Author: jorgehog
 * 
 * Created on 30. mars 2012, 17:42
 */

#include "QMC.h"
#include "System.h"
#include "Jastrow.h"
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
    } else {
        get_wf_value(walker_postdiff);
    }
}


