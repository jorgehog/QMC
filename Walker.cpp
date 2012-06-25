/* 
 * File:   Walker.cpp
 * Author: jorgehog
 * 
 * Created on 30. mars 2012, 16:50
 */

#include <math.h>

#include "Walker.h"
#include "lib.h"
using namespace arma;

Walker::Walker(int n_p, int dim) {
    this->dim = dim;
    this->n_p = n_p;
    this->n2 = n_p / 2;



    //need memory optimization for BF? Nah..
    r = zeros<mat > (n_p, dim);
    r_rel = zeros<mat > (n_p, n_p);
    qforce = zeros<mat > (n_p, dim);
    inv = zeros<mat > (n2, n_p);
    jast_grad = zeros<mat > (n_p, dim);
    spatial_grad = zeros<mat > (n_p, dim);
    value = 0;
    lapl_sum = 0;
    slater_ratio = 0;

}

double Walker::abs_relative(int i, int j) {
    int k;
    double r_ij, tmp;

    r_ij = 0;
    for (k = 0; k < dim; k++) {
        tmp = (r(i, k) - r(j, k));
        r_ij += tmp*tmp;
    }
    r_ij = sqrt(r_ij);

    return r_ij;
}

double Walker::get_r_i2(int i) const {
    int j;
    double r2;

    r2 = 0;
    for (j = 0; j < dim; j++) {
        r2 += r(i, j) * r(i, j);
    }

    return r2;
}

void Walker::make_rel_matrix() {
    int i, j;


    for (i = 0; i < n_p - 1; i++) {
        for (j = i + 1; j < n_p; j++) {
            r_rel(i, j) = r_rel(j, i) = abs_relative(i, j);
        }
    }
}

bool Walker::is_singular() {
    int i, j;
    double eps;

    eps = 0.1;

    for (i = 0; i < n_p; i++) {
        for (j = i + 1; j < n_p; j++) {
            if (r_rel(i, j) < eps) {
                return true;
            }
        }
    }

    return false;
}

bool Walker::check_bad_qforce() {
    double qforce_test = 0;
    
    for (int i = 0; i < n_p; i++) {
        for (int j = 0; j < dim; j++) {
            double tmp = qforce(i, j); 
            if (tmp*tmp > qforce_test) {
                qforce_test = tmp*tmp;
            }
        }
    }
 
    if (qforce_test > 1000){
        return true;
    } else {
        return false;
    }
    
}