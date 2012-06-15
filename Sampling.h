/* 
 * File:   Sampling.h
 * Author: jorgehog
 *
 * Created on 15. juni 2012, 18:44
 */

#ifndef SAMPLING_H
#define	SAMPLING_H

#include <fstream>

class QMC;

class Sampling {
protected:
    int n_p;
    int dim;

    Diffusion* diffusion;
    QMC* qmc;
    bool is_importance;

public:
    Sampling(int n_p, int dim);
    void set_trial_pos(Walker &walker, bool load_VMC_dist = false, std::ifstream* file = NULL);
    virtual void get_necessities(Walker &walker) = 0;

    void set_qmc_ptr(QMC* qmc) {
        this->qmc = qmc;
    }

    bool get_importance_bool() {
        return is_importance;
    }

};

class Importance : public Sampling {
public:
    Importance(int n_p, int dim, double timestep, double D = 0.5);

    virtual void get_necessities(Walker& walker);

};

class Brute_Force : public Sampling {
public:
    Brute_Force(int n_p, int dim, double timestep, double D = 0.5);

    virtual void get_necessities(Walker& walker);
};

#endif	/* SAMPLING_H */

