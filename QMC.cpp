/* 
 * File:   QMC.cpp
 * Author: jorgehog
 * 
 * Created on 30. mars 2012, 17:42
 */

#include "QMC.h"
#include "System.h"
#include "Jastrow.h"

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

double QMC::get_wf_value(Walker& walker) {
    double value;

    value = system.get_spatial_wf(walker) * jastrow.get_val(walker);

    return value;
}


