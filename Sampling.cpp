/* 
 * File:   Sampling.cpp
 * Author: jorgehog
 * 
 * Created on 15. juni 2012, 18:44
 */

#include "Sampling.h"
#include "Diffusion.h"
#include "Walker.h"
#include "QMC.h"

Sampling::Sampling(int n_p, int dim) {
    this->n_p = n_p;
    this->dim = dim;
}

Importance::Importance(int n_p, int dim, double timestep, double D) : Sampling(int n_p, int dim) {
    is_importance = true;
    diffusion = new Fokker_Planck(n_p, dim, timestep, D);
}

Brute_Force::Brute_Force(int n_p, int dim, double timestep, double D) : Sampling(int n_p, int dim) {
    is_importance = false;
    diffusion = new Simple(n_p, dim, timestep, D);
}

Sampling::set_trial_pos(Walker &walker, bool load_VMC_dist, std::ifstream* file) {
    int i, j;

    if (load_VMC_dist) {

        double pos;
        for (i = 0; i < n_p; i++) {
            for (j = 0; j < dim; j++) {
                file >> pos;
                walker.r[i][j] = pos;
            }
        }
    } else {
        walker.r[i][j] = diffusion->get_new_pos();
    }

    walker.make_rel_matrix();

    get_necessities(walker);

}

Brute_Force::get_necessities(Walker& walker) {
    if (qmc->get_kinetic_bool()) {
        system.initialize_for_CF(walker);
    }

    get_wf_value(wfold);
}
