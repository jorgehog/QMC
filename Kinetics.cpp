/* 
 * File:   Kinetics.cpp
 * Author: jorgehog
 * 
 * Created on 13. april 2012, 17:45
 */

#include "Kinetics.h"
#include "System.h"
#include "QMC.h"
#include "Walker.h"

Kinetics::Kinetics(int n_p, int dim) {
    this->n_p = n_p;
    this->n2 = n_p / 2;
    this->dim = dim;
}

Numerical::Numerical(int n_p, int dim, double h)
: Kinetics(n_p, dim) {
    this->h = h;
    this->h2 = 1. / (h * h);

    wfminus = new Walker(n_p, dim);
    wfplus = new Walker(n_p, dim);


}

double Numerical::get_KE(Walker* walker) {
    int i, j;
    double e_kinetic, wf, wf_min, wf_plus;

    //kinetic energy:

    wf = walker->value;

    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            wfplus->r[i][j] = wfminus->r[i][j] = walker->r[i][j];
        }
    }

    e_kinetic = 0;
    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            wfplus->r[i][j] = walker->r[i][j] + h;
            wfminus->r[i][j] = walker->r[i][j] - h;

            wfplus->make_rel_matrix();
            wfminus->make_rel_matrix();


            qmc->get_wf_value(wfplus);
            qmc->get_wf_value(wfminus);

            wf_min = wfminus->value;
            wf_plus = wfplus->value;

            e_kinetic -= (wf_min + wf_plus - 2 * wf);
            wfplus->r[i][j] = walker->r[i][j];
            wfminus->r[i][j] = walker->r[i][j];
        }
    }

    e_kinetic = 0.5 * h2 * e_kinetic / wf;

    return e_kinetic;
}

void Numerical::get_QF(Walker* walker) {
    int i, j;
    double wf_min, wf_plus, wf;

    wf = walker->value;

    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            wfplus->r[i][j] = wfminus->r[i][j] = walker->r[i][j];
        }
    }


    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            wfplus->r[i][j] = walker->r[i][j] + h;
            wfminus->r[i][j] = walker->r[i][j] - h;

            wfplus->make_rel_matrix();
            wfminus->make_rel_matrix();

            qmc->get_wf_value(wfplus);
            qmc->get_wf_value(wfminus);

            wf_min = wfminus->value;
            wf_plus = wfplus->value;

            walker->qforce[i][j] = (wf_plus - wf_min) / (wf * h);

            wfplus->r[i][j] = walker->r[i][j];
            wfminus->r[i][j] = walker->r[i][j];

        }
    }
}

void Numerical::update_necessities_IS(Walker* walker_pre, Walker* walker_post, int particle) {
    qmc->get_system_ptr()->calc_for_newpos(walker_pre, walker_post, particle);
    qmc->get_wf_value(walker_post);
}

void Numerical::calculate_energy_necessities_BF(Walker* walker) {
    //No necessities.
    //laplace?
}

void Numerical::update_walker_IS(Walker* walker_pre, Walker* walker_post, int particle) {
    walker_post->value = walker_pre->value;
}

void Numerical::copy_walker_BF(Walker* parent, Walker* child) {
    child->value = parent->value;
}

void Numerical::copy_walker_IS(Walker* parent, Walker* child) {
    qmc->get_system_ptr()->copy_walker(parent, child);
}

Closed_form::Closed_form(int n_p, int dim)
: Kinetics(n_p, dim) {

}

void Closed_form::update_walker_IS(Walker* walker_pre, Walker* walker_post, int particle) {
    int start = n2 * (particle >= n2);

    for (int i = start; i < start + n2; i++) {
        for (int j = 0; j < dim; j++) {
            walker_pre->spatial_grad[i][j] = walker_post->spatial_grad[i][j];
        }
    }

    for (int i = 0; i < n_p; i++) {
        for (int j = 0; j < dim; j++) {
            walker_pre->jast_grad[i][j] = walker_post->jast_grad[i][j];
        }
    }
}

double Closed_form::get_KE(Walker* walker) {
    int i, j;
    double xterm, e_kinetic;


    e_kinetic = xterm = 0;

    //the X-term
    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            xterm += walker->jast_grad[i][j] * walker->spatial_grad[i][j];
        }
    }


    e_kinetic = 2 * xterm + walker->lapl_sum; //LAPLACE??S


    return -0.5 * e_kinetic;
}

void Closed_form::get_QF(Walker* walker) {
    int i, j;

    for (i = 0; i < n_p; i++) {
        for (j = 0; j < dim; j++) {
            walker->qforce[i][j] = 2 * (walker->jast_grad[i][j] + walker->spatial_grad[i][j]);
        }
    }
}

void Closed_form::calculate_energy_necessities_BF(Walker* walker) {
    qmc->get_system_ptr()->initialize(walker);
    qmc->get_gradients(walker);
    //laplace?
}

void Closed_form::update_necessities_IS(Walker* walker_pre, Walker* walker_post, int particle) {
    qmc->get_system_ptr()->calc_for_newpos(walker_pre, walker_post, particle);
    qmc->get_gradients(walker_post, particle);
}

void Closed_form::copy_walker_BF(Walker* parent, Walker* child) {
    for (int i = 0; i < n_p; i++) {
        for (int j = 0; j < dim; j++) {
            child->jast_grad[i][j] = parent->jast_grad[i][j];
            child->spatial_grad[i][j] = parent->spatial_grad[i][j];
        }
    }

    qmc->get_system_ptr()->copy_walker(parent, child);

    child->value = parent->value;
}

void Closed_form::copy_walker_IS(Walker* parent, Walker* child) {
    for (int i = 0; i < n_p; i++) {
        for (int j = 0; j < dim; j++) {
            child->jast_grad[i][j] = parent->jast_grad[i][j];
            child->spatial_grad[i][j] = parent->spatial_grad[i][j];
        }
    }

    qmc->get_system_ptr()->copy_walker(parent, child);
}
