/* 
 * File:   System.cpp
 * Author: jorgehog
 * 
 * Created on 30. mars 2012, 16:49
 */

#include "QMCheaders.h"

System::System(int n_p, int dim, Potential* pot, Orbitals* orbital) {
    this->n_p = n_p;
    this->dim = dim;

    this->pot = pot;
    this->orbital = orbital;
}

double System::get_potential_energy(const Walker* walker) const {
    return pot->get_pot_E(walker);
}

Fermions::Fermions(int n_p, int dim, Potential* pot, Orbitals* orbital)
: System(n_p, dim, pot, orbital) {

    n2 = n_p / 2;

    s_up = arma::zeros<arma::mat > (n_p / 2, n_p / 2);
    s_down = arma::zeros<arma::mat > (n_p / 2, n_p / 2);

}

void Fermions::initialize(Walker* walker) {
    make_merged_inv(walker);
}

void Fermions::get_spatial_grad(Walker* walker, int particle) const {
    int i, j, k, start;


    start = n2 * (particle >= n2);

    walker->spatial_grad(span(start, start + n2 -1 ), span(0, dim-1)) = arma::zeros<mat>(n2, dim);

    //updating the part with the same spin as the moved particle
    for (i = start; i < n2 + start; i++) {
        for (j = 0; j < n2; j++) {
            for (k = 0; k < dim; k++) {
                walker->spatial_grad(i, k) += orbital->del_phi(walker, i, j, k) * walker->inv(j, i);
            }
        }
    }
}

void Fermions::initialize_slaters(const Walker* walker) {
    int i, q_num;

    for (i = 0; i < n2; i++) {
        for (q_num = 0; q_num < n2; q_num++) {
            s_up(i, q_num) = orbital->phi(walker, i, q_num);
            s_down(i, q_num) = orbital->phi(walker, i + n2, q_num);
        }
    }

    //    cout <<"UP"<< s_down*walker->inv(span(0,2), span(3,5)) << endl;
    //    cout <<"DOWN"<< s_up*walker->inv(span(0,2),span(0,2)) << endl;
}

double Fermions::get_det() {
    return arma::det(s_up) * arma::det(s_down);
}

void Fermions::invert_slaters() {
    s_up = arma::inv(s_up);
    s_down = arma::inv(s_down);
}

void Fermions::make_merged_inv(Walker* walker) {
    int i, j;

    initialize_slaters(walker);
    invert_slaters();

    //merging the inverse matrices
    for (i = 0; i < n2; i++) {
        for (j = 0; j < n2; j++) {
            walker->inv(i, j) = s_up(i, j);
            walker->inv(i, j + n2) = s_down(i, j);
        }
    }
}

double Fermions::get_spatial_wf(const Walker* walker) {
    initialize_slaters(walker);
    return get_det();
}

double Fermions::get_spatial_ratio(const Walker* walker_pre, const Walker* walker_post, int particle) const {
    int q_num;
    double s_ratio;

    s_ratio = 0;
    for (q_num = 0; q_num < n2; q_num++) {
        s_ratio += orbital->phi(walker_post, particle, q_num) * walker_pre->inv(q_num, particle);
    }

    return s_ratio;
}

void Fermions::update_inverse(const Walker* walker_old, Walker* walker_new, int particle) const {
    int k, l, j, start;
    double sum;

    start = n2 * (particle >= n2);

    //updating the part of the inverse with the same spin as particle i
    for (k = 0; k < n2; k++) {
        for (j = start; j < n2 + start; j++) {
            sum = 0;
            if (j == particle) {
                for (l = 0; l < n2; l++) {
                    sum += orbital->phi(walker_old, particle, l) * walker_old->inv(l, j);
                }
                walker_new->inv(k, j) = walker_old->inv(k, particle) / walker_new->slater_ratio*sum;
            } else {
                for (l = 0; l < n2; l++) {
                    sum += orbital->phi(walker_new, particle, l) * walker_old->inv(l, j);
                }
                walker_new->inv(k, j) = walker_old->inv(k, j) - walker_old->inv(k, particle) / walker_new->slater_ratio*sum;
            }
        }
    }
}

void Fermions::calc_for_newpos(const Walker* walker_old, Walker* walker_new, int particle) const {
    update_inverse(walker_old, walker_new, particle);
}

double Fermions::get_spatial_lapl_sum(const Walker* walker) const {
    int i, j;
    double sum;

    sum = 0;
    for (i = 0; i < n_p; i++) {
        for (j = 0; j < n_p / 2; j++) {
            sum += orbital->lapl_phi(walker, i, j) * walker->inv(j, i);
        }
    }

    return sum;
}

void Fermions::update_walker(Walker* walker_pre, const Walker* walker_post, int particle) const {
    int start = n2 * (particle >= n2);

    //Reseting the parts with the same spin as the moved particle
    for (int i = start; i < start + n2; i++) {
        for (int j = 0; j < n2; j++) {
            walker_pre->inv(j, i) = walker_post->inv(j, i);
        }
    }
}

void Fermions::copy_walker(const Walker* parent, Walker* child) const {
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n_p; j++) {
            child->inv(i, j) = parent->inv(i, j);
        }
    }
}

void Fermions::reset_walker_ISCF(const Walker* walker_pre, Walker* walker_post, int particle) const {

    int start = n2 * (particle >= n2);

    //Reseting the part of the inverse with the same spin as particle i
    for (int i = 0; i < n2; i++) {
        for (int j = start; j < n2 + start; j++) {
            walker_post->inv(i, j) = walker_pre->inv(i, j);
        }
    }
}
