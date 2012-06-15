/* 
 * File:   System.cpp
 * Author: jorgehog
 * 
 * Created on 30. mars 2012, 16:49
 */

#include "System.h"
#include "Jastrow.h"
#include "Walker.h"

System::System() {

}

Fermions::Fermions(int n_p, int dim, Potential pot, Kinetics kin, Orbitals orbital) {
    this->n_p = n_p;
    this->dim = dim;
    this->pot = pot;

    this->orbital = orbital;

    s_up = (double **) matrix(n_p / 2, n_p / 2, sizeof (double));
    s_down = (double **) matrix(n_p / 2, n_p / 2, sizeof (double));

}

void Fermions::initialize_for_CF(Walker& walker) {
    make_merged_inv(wf);
    get_init_grad(wf, jastrow);
}


//MUST HAVE NEW INV HERE

void Fermions::get_spatial_grad(Walker& walker, int particle) {
    int i, j, k, start;


    start = n2 * (particle >= n2);
    //    if (particle >= n2) {
    //        start = n2;
    //    } else {
    //        start = 0;
    //    }

    //    //if the last metropolis-test went through, there is no need to overwrite data
    //    if (accepted_last == false) {
    //        for (i = n2 - start; i < n_p - start; i++) {
    //            for (k = 0; k < dim; k++) {
    //                wf_new.spatial_grad[i][k] = wf_old.spatial_grad[i][k];
    //            }
    //        }
    //    }


    //updating the part with the same spin as the moved particle
    for (i = start; i < n2 + start; i++) {
        for (k = 0; k < dim; k++) {
            walker.spatial_grad[i][k] = 0;

            for (j = 0; j < n2; j++) {
                walker.spatial_grad[i][k] += orbital.del_phi(walker, i, j, k) * walker.inv[j][i];
            }

        }
    }
}

void Fermions::initialize_slaters(const Walker& walker) {
    int i, q_num;

    for (i = 0; i < n2; i++) {
        for (q_num = 0; q_num < n2; q_num++) {
            s_up[i][q_num] = orbital.phi(walker, i, q_num);
            s_down[i][q_num] = orbital.phi(walker, i + n2, q_num);
        }
    }
}

double Fermions::get_det() {
    int i;
    double det, g1, g2;
    int *dummy = new int[n2];

    ludcmp(s_up, n2, dummy, &g1);
    ludcmp(s_down, n2, dummy, &g2);

    det = 1;
    for (i = 0; i < n2; i++) {
        det *= s_up[i][i] * s_down[i][i];
    }

    delete[] dummy;

    return g1 * g2*det;
}

void Fermions::invert_slaters() {
    int i, j;
    double d;
    // allocate space in memory
    int* indx = new int[n2];
    double* col = new double[n2];
    double** y = (double **) matrix(n2, n2, sizeof (double));


    //SPIN UP:
    ludcmp(s_up, n2, indx, &d); // LU decompose a

    // find inverse of a by columns
    for (j = 0; j < n2; j++) {
        // initialize right-side of linear equations
        for (i = 0; i < n2; i++) col[i] = 0.0;
        col[j] = 1.0;
        lubksb(s_up, n2, indx, col);
        // save result in y
        for (i = 0; i < n2; i++) y[i][j] = col[i];
    } //j-loop over columns
    // return the inverse matrix in a
    for (i = 0; i < n2; i++) {
        for (j = 0; j < n2; j++) s_up[i][j] = y[i][j];
    }


    //SPIN DOWN:
    ludcmp(s_down, n2, indx, &d); // LU decompose a

    // find inverse of a by columns
    for (j = 0; j < n2; j++) {
        // initialize right-side of linear equations
        for (i = 0; i < n2; i++) col[i] = 0.0;
        col[j] = 1.0;
        lubksb(s_down, n2, indx, col);
        // save result in y
        for (i = 0; i < n2; i++) y[i][j] = col[i];
    } //j-loop over columns
    // return the inverse matrix in a
    for (i = 0; i < n2; i++) {
        for (j = 0; j < n2; j++) s_down[i][j] = y[i][j];
    }

    delete[] col;
    delete[] indx;
    free_matrix((void **) y);

}

void Fermions::make_merged_inv(const Walker& walker) {
    int i, j;

    initialize_slaters(walker);
    invert_slaters();

    //merging the inverse matrices
    for (i = 0; i < n2; i++) {
        for (j = 0; j < n2; j++) {
            walker.inv[i][j] = s_up[i][j];
            walker.inv[i][j + n2] = s_down[i][j];
        }
    }
}

double Fermions::get_spatial_wf(const Walker& walker) {
    initialize_slaters(walker);
    return get_det();
}

double Fermions::get_spatial_ratio(const Walker& walker_new, const Walker& walker_old, int particle) {
    int q_num;
    double s_ratio;

    s_ratio = 0;
    for (q_num = 0; q_num < n2; q_num++) {
        s_ratio += orbital.phi(walker_new, particle, q_num) * walker_old.inv[q_num][particle];
    }

    walker_new.ratio = s_ratio;
    return s_ratio;
}

Fermions::update_inverse(Walker& walker_old, Walker& walker_new, int particle) {
    int k, l, j, start;
    double sum;

    start = n2 * (particle >= n2);

    //updating the part of the inverse with the same spin as particle i
    for (k = 0; k < n2; k++) {
        for (j = start; j < n2 + start; j++) {
            sum = 0;
            if (j == particle) {
                for (l = 0; l < n2; l++) {
                    sum += orbital.phi(walker_old, particle, l) * walker_old.inv[l][j];
                }
                walker_new.inv[k][j] = walker_old.inv[k][particle] / walker_new.ratio*sum;
            } else {
                for (l = 0; l < n2; l++) {
                    sum += orbital.phi(walker_new, particle, l) * walker_old.inv[l][j];
                }
                walker_new.inv[k][j] = walker_old.inv[k][j] - walker_old.inv[k][particle] / walker_new.ratio*sum;
            }
        }
    }
}

void Fermions::calc_for_newpos(const Walker& walker_old, Walker& walker_new, int particle) {
    update_inverse(walker_old, walker_new, particle);
}

double Fermions::get_spatial_lapl_sum(const Walker& walker_new, const Walker &walker_old) {
    int i, j;
    double sum;

    sum = 0;
    for (i = 0; i < n_p; i++) {
        for (j = 0; j < n_p / 2; j++) {
            sum += orbital.lapl_phi(walker_new, i, j) * walker_old.inv[j][i];
        }
    }

    return sum;
}
