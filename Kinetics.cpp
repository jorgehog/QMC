/* 
 * File:   Kinetics.cpp
 * Author: jorgehog
 * 
 * Created on 13. april 2012, 17:45
 */

#include "Kinetics.h"
#include "System.h"

Kinetics::Kinetics() {

}

Numerical::Numerical(int n_p, int dim, double h) {
    this->h = h;
    this->h2 = 1. / (h * h);
    this->n_p = n_p;
    this->dim = dim;
}

double Numerical::get_KE(Walker& walker, System& system) {
    int i, j;
    double e_kinetic, wf, wf_min, wf_plus;

    //kinetic energy:

    wf = system.get_wf_val(walker);

    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            wfplus.r[i][j] = wfminus.r[i][j] = walker.r[i][j];
        }
    }

    e_kinetic = 0;
    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            wfplus.r[i][j] = walker.r[i][j] + h;
            wfminus.r[i][j] = walker.r[i][j] - h;

            wfplus.make_rel_matrix();
            wfminus.make_rel_matrix();

            system.get_wf_val(wfplus);
            system.get_wf_val(wfminus);

            e_kinetic -= (wf_min + wf_plus - 2 * wf);
            wfplus.r[i][j] = walker.r[i][j];
            wfminus.r[i][j] = walker.r[i][j];
        }
    }

    e_kinetic = 0.5 * h2 * e_kinetic / wf;

    return e_kinetic;
}

void Numerical::get_QF(Walker& walker, System& system) {
    int i, j;
    double wf_min, wf_plus, wf;

    wf = system.get_wf_val(walker);

    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            wfplus.r[i][j] = wfminus.r[i][j] = walker.r[i][j];
        }
    }


    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            wfplus.r[i][j] = walker.r[i][j] + h;
            wfminus.r[i][j] = walker.r[i][j] - h;

            wfplus.make_rel_matrix();
            wfminus.make_rel_matrix();

            system.get_wf_val(wfplus);
            system.get_wf_val(wfminus);

            walker.qforce[i][j] = (wf_plus - wf_min) / (wf * h);

            wfplus.r[i][j] = walker.r[i][j];
            wfminus.r[i][j] = walker.r[i][j];

        }
    }
}

Closed_form::Closed_form(int n_p, int dim) {
    this->n_p = n_p;
    this->dim = dim;
}

double Closed_form::get_KE(Walker& walker, System &system) {
    int i, j;
    double xterm, e_kinetic;


    e_kinetic = xterm = 0;

    //the X-term
    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            xterm += walker.jast_grad[i][j] * walker.spatial_grad[i][j];
        }
    }
    e_kinetic += 2 * xterm;

    //laplacian terms
    e_kinetic += system.get_lapl_sum(walker);


    return -0.5 * e_kinetic;
}

void Closed_form::get_QF(Walker& walker, System &system) {
    int i, j;
    
    system.get_gradients(walker);

    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            walker.qforce[i][j] = 2 * (walker.jast_grad[i][j] + walker.spatial_grad[i][j]);
        }
    }
}


