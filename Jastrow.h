/* 
 * File:   Jastrow.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:52
 */

#ifndef JASTROW_H
#define	JASTROW_H

#include "Walker.h"
#include <armadillo>

class Jastrow {
protected:
    int n_p;
    int n2;
    int dim;


public:
    Jastrow(int n_p, int dim);
    Jastrow();

    virtual void initialize() = 0;

    virtual double get_val(Walker* walker) = 0;
    virtual double get_j_ratio(Walker* walker_new, Walker* walker_old, int i) = 0;
    virtual void get_grad(Walker* walker) = 0;
    //void get_grad(Walker* walker); In walker
    virtual double get_lapl_sum(const Walker* walker) const = 0;

};

class No_Jastrow : public Jastrow {
public:

    No_Jastrow();

    virtual void get_grad(Walker* walker) {
        
    };

    virtual void initialize() {
    };

    virtual double get_j_ratio(Walker* walker_post, Walker* walker_pre, int i) {
        return 1;
    };

    virtual double get_val(Walker* walker) {
        return 1;
    };

    virtual double get_lapl_sum(const Walker* walker) const {
        return 0;
    };
};

class Pade_Jastrow : public Jastrow {
protected:
    double beta;
    arma::mat a;

public:

    Pade_Jastrow(int n_p, int dim, double beta);

    virtual void initialize();

    virtual void get_grad(Walker* walker);

    virtual double get_j_ratio(Walker* walker_new, Walker* walker_old, int i);
    virtual double get_val(Walker* walker);
    virtual double get_lapl_sum(const Walker* walker) const;

};

#endif	/* JASTROW_H */

