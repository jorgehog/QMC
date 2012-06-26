/* 
 * File:   Jastrow.cpp
 * Author: jorgehog
 * 
 * Created on 30. mars 2012, 16:52
 */

#include "QMCheaders.h"

Jastrow::Jastrow(int n_p, int dim) {
    this->n_p = n_p;
    this->n2 = n_p / 2;
    this->dim = dim;
}

Jastrow::Jastrow(){
    
}

No_Jastrow::No_Jastrow() {

}

Pade_Jastrow::Pade_Jastrow(int n_p, int dim, double beta)
: Jastrow(n_p, dim) {

    this->beta = beta;
    
    a = arma::zeros<arma::mat>(n_p, n_p);
}

void Pade_Jastrow::initialize() {
    int i, j;
    double a_sym, a_asym;

    if (dim == 2) {
        a_sym = 1. / 3;
        a_asym = 1.0;
    } else if (dim == 3) {
        a_sym = 1. / 4;
        a_asym = 1. / 2;
    } else {
        std::cout << "Unable to initialize Jastrow paremters: Unknown dimension" << std::endl;
        exit(1);
    }

    for (i = 0; i < n_p; i++) {
        for (j = 0; j < n_p; j++) {

            if ((j < n2 && i < n2) || (j >= n2 && i >= n2)) {
                a(i,j) = a_sym;
            } else {
                a(i,j) = a_asym;
            }
        }
    }
}

double Pade_Jastrow::get_val(const Walker* walker) const{
    int i, j;
    double arg;

    arg = 0;
    for (i = 0; i < n_p - 1; i++) {
        for (j = i + 1; j < n_p; j++) {
            arg += a(i,j) * walker->r_rel(i,j) / (1.0 + beta * walker->r_rel(i,j));
        }
    }

    return exp(arg);
}

void Pade_Jastrow::get_grad(Walker* walker) const{
    int i, j, k;
    double b_ij, deriv;

    for (i = 0; i < n_p; i++) {
        for (k = 0; k < dim; k++) {
            deriv = 0;
            for (j = 0; j < i; j++) {
                b_ij = 1.0 + beta * walker->r_rel(i,j);
                deriv += a(i,j) * (walker->r(i,k) - walker->r(j,k)) / (walker->r_rel(i,j) * b_ij * b_ij);
            }
            for (j = i + 1; j < n_p; j++) {
                b_ij = 1.0 + beta * walker->r_rel(i,j);
                deriv += a(i,j) * (walker->r(i,k) - walker->r(j,k)) / (walker->r_rel(i,j) * b_ij * b_ij);
            }

            walker->jast_grad(i,k) = deriv;
        }
    }

}

double Pade_Jastrow::get_j_ratio(const Walker* walker_new, const Walker* walker_old, int i) const{
    int j;
    double j_ratio;

    j_ratio = 0;
    for (j = 0; j < n_p; j++) {
        j_ratio += a(i,j) * (walker_new->r_rel(i,j) / (1.0 + beta * walker_new->r_rel(i,j)) -
                walker_old->r_rel(i,j) / (1.0 + beta * walker_old->r_rel(i,j)));
    }


    return exp(j_ratio);
}

double Pade_Jastrow::get_lapl_sum(const Walker* walker) const {
    int k, j, d;
    double sum1, sum2, b_kj;

    sum1 = sum2 = 0;

    for (k = 0; k < n_p; k++) {
        for (j = k + 1; j < n_p; j++) {
            b_kj = 1 + beta * walker->r_rel(k,j);
            sum2 += a(k,j) * (1 - beta * walker->r_rel(k,j)) / (walker->r_rel(k,j) * b_kj * b_kj * b_kj);
        }

        for (d = 0; d < dim; d++) {
            sum1 += walker->jast_grad(k,d) * walker->jast_grad(k,d);
        }
    }

    return sum1 + 2 * sum2;
}
