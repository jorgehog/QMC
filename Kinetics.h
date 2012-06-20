/* 
 * File:   Kinetics.h
 * Author: jorgehog
 *
 * Created on 13. april 2012, 17:45
 */

#ifndef KINETICS_H
#define	KINETICS_H


class Walker;
class QMC;

class Kinetics {
protected:
    int n_p;
    int n2;
    int dim;

    bool closed_form;

    QMC *qmc;

public:


    Kinetics(int n_p, int dim);

    virtual double get_KE(Walker* walker) = 0;
    virtual void get_QF(Walker* walker) = 0;

    virtual void update_walker_IS(Walker* walker_pre, Walker* walker_post, int particle) = 0;
    virtual void calculate_energy_necessities_BF(Walker* walker) = 0;
    virtual void update_necessities_IS(Walker* walker_pre, Walker* walker_post, int particle) = 0;
    virtual void copy_walker_IS(Walker* parent, Walker* child) = 0;
    virtual void copy_walker_BF(Walker* parent, Walker* child) = 0;

    bool get_closed_form() {
        return closed_form;
    }

    void set_qmc_ptr(QMC* qmc) {
        this->qmc = qmc;
    }
};

class Numerical : public Kinetics {
protected:
    double h, h2;

    Walker* wfplus;
    Walker* wfminus;

public:
    Numerical(int n_p, int dim, double h = 0.0001);

    virtual double get_KE(Walker* walker);
    virtual void get_QF(Walker* walker);

    virtual void update_walker_IS(Walker* walker_pre, Walker* walker_post, int particle);
    virtual void calculate_energy_necessities_BF(Walker* walker);
    virtual void update_necessities_IS(Walker* walker_pre, Walker* walker_post, int particle);
    virtual void copy_walker_IS(Walker* parent, Walker* child);
    virtual void copy_walker_BF(Walker* parent, Walker* child);

};

class Closed_form : public Kinetics {
public:
    Closed_form(int n_p, int dim);

    virtual double get_KE(Walker* walker);
    virtual void get_QF(Walker* walker);

    virtual void update_walker_IS(Walker* walker_pre, Walker* walker_post, int particle);
    virtual void calculate_energy_necessities_BF(Walker* walker);
    virtual void update_necessities_IS(Walker* walker_pre, Walker* walker_post, int particle);

    virtual void copy_walker_IS(Walker* parent, Walker* child);
    virtual void copy_walker_BF(Walker* parent, Walker* child);
};

#endif	/* KINETICS_H */

