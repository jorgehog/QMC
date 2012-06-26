/* 
 * File:   QMC.cpp
 * Author: jorgehog
 * 
 * Created on 30. mars 2012, 17:42
 */

#include "QMCheaders.h"

QMC::QMC(int n_p, int dim, int n_c, Jastrow *jastrow, Sampling *sampling, System *system, Kinetics *kinetics) {
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



void QMC::get_gradients(Walker* walker, int particle) const {
    jastrow->get_grad(walker);
    system->get_spatial_grad(walker, particle);
}

void QMC::get_gradients(Walker* walker) const {
    jastrow->get_grad(walker);
    system->get_spatial_grad(walker, 0);
    system->get_spatial_grad(walker, n2);
}

void QMC::get_laplsum(Walker* walker) const {
    walker->lapl_sum = system->get_spatial_lapl_sum(walker) + jastrow->get_lapl_sum(walker);
}

void QMC::get_wf_value(Walker* walker) const {
    walker->value = system->get_spatial_wf(walker) * jastrow->get_val(walker);
}

void QMC::update_pos(const Walker* walker_pre, Walker* walker_post, int particle) const {

    for (int j = 0; j < dim; j++) {
        walker_post->r(particle, j) = walker_pre->r(particle, j)
                + sampling->get_new_pos(walker_pre, particle, j);
    }

    for (int j = 0; j < n_p; j++) {
        if (j != particle) {
            walker_post->r_rel(particle, j) = walker_post->r_rel(j, particle)
                    = walker_post->abs_relative(particle, j);
        }
    }
}

void QMC::update_necessities(const Walker* walker_pre, Walker* walker_post, int particle) const {
    sampling->update_necessities(walker_pre, walker_post, particle);
}

double QMC::get_acceptance_ratio(const Walker* walker_pre, const Walker* walker_post, int particle) const {
    double spatial_jast = sampling->get_spatial_ratio(walker_post, walker_pre, particle);
    double G = sampling->get_g_ratio(walker_post, walker_pre, particle);

    return spatial_jast * spatial_jast * G;
}

void QMC::calculate_energy_necessities(Walker* walker) const {
    kinetics->calculate_energy_necessities(walker);
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

void QMC::update_walker(Walker* walker_pre, const Walker* walker_post, int particle) const {
    sampling->update_walker(walker_pre, walker_post, particle);
}

void QMC::reset_walker(const Walker* walker_pre, Walker* walker_post, int particle) const {
    for (int i = 0; i < dim; i++) {
        walker_post->r(particle, i) = walker_pre->r(particle, i);
    }

    for (int i = 0; i < n_p; i++) {
        walker_post->r_rel(i, particle) = walker_post->r_rel(particle, i) = walker_pre->r_rel(i, particle);
    }

    sampling->reset_walker(walker_pre, walker_post, particle);
}

void QMC::copy_walker(const Walker* parent, Walker* child) const {
    for (int i = 0; i < n_p; i++) {
        for (int j = 0; j < dim; j++) {
            child->r(i, j) = parent->r(i, j);
        }

        for (int k = i + 1; k < n_p; k++) {
            child->r_rel(i, k) = child->r_rel(k, i) = parent->r_rel(i, k);
        }
    }

    sampling->copy_walker(parent, child);


}

VMC::VMC(int n_p, int dim, int n_c, Jastrow *jastrow, Sampling *sampling, System *system, Kinetics *kinetics, bool dist_to_file)
: QMC(n_p, dim, n_c, jastrow, sampling, system, kinetics) {

    vmc_E = 0;
    E2 = 0;

    wfold = new Walker(n_p, dim);
    wfnew = new Walker(n_p, dim);

    this->dist_to_file = dist_to_file;
}

void VMC::initialize() {
    jastrow->initialize();
    sampling->set_trial_pos(wfold);
    copy_walker(wfold, wfnew);
}

void VMC::calculate_energy(const Walker* walker) {
    double local_E;

    local_E = kinetics->get_KE(walker);
    local_E += system->get_potential_energy(walker);

    vmc_E += local_E;
    E2 += local_E*local_E;
}

void VMC::scale_values() {
    vmc_E /= n_c;
    E2 /= n_c;
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
                reset_walker(wfold, wfnew, particle);
            }
        }

        calculate_energy_necessities(wfold);
        calculate_energy(wfold);

    }

    scale_values();

}

void VMC::output() const {
    std::cout << "VMC energy: " << get_energy() << std::endl;
    std::cout << "VMC variance: " << get_var() << std::endl;
    std::cout << "Acceptance ratio: " << accepted / (double) (n_c * n_p) << endl;
}

double VMC::get_var() const {
    return E2 - vmc_E*vmc_E;
}

double VMC::get_e2() const {
    return E2;
}

void VMC::set_e(double E) {
    vmc_E = E;
}

void VMC::set_e2(double E2) {
    this->E2 = E2;
}

double VMC::get_energy() const {
    return vmc_E;
}
