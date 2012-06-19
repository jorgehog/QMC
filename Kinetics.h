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
    int dim;

    bool closed_form;

    QMC *qmc;

public:


    Kinetics();

    virtual double get_KE(Walker &walker, System &system) = 0;
    virtual void get_QF(Walker &walker, System &system) = 0;

    virtual void calculate_energy_necessities_BF(Walker &walker) = 0;
    virtual void update_necessities_IS(Walker &walker_pre, Walker& walker_post, int particle) = 0;

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

    Walker wfplus;
    Walker wfminus;

public:
    Numerical(int n_p, int dim, double h = 0.0001);

    virtual double get_KE(Walker &walker, System &system);
    virtual void get_QF(Walker &walker, System &system);

    virtual void calculate_energy_necessities_BF(Walker &walker);
    virtual void update_necessities_IS(Walker &walker_pre, Walker& walker_post, int particle);

};

class Closed_form : public Kinetics {
public:
    Closed_form(int n_p, int dim);

    virtual double get_KE(Walker &walker, System &system);
    virtual void get_QF(Walker &walker, System &system);

    virtual void calculate_energy_necessities_BF(Walker &walker) ;
    virtual void update_necessities_IS(Walker &walker_pre, Walker& walker_post, int particle);
};

#endif	/* KINETICS_H */

