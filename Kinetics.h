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

    QMC *qmc;

public:


    Kinetics(int n_p, int dim);

    virtual double get_KE(Walker* walker) = 0;
    virtual void get_QF(Walker* walker) = 0;

    virtual void get_necessities_IS(Walker* walker) = 0;
    //BF necessities are independent of kinetics

    virtual void update_walker_IS(Walker* walker_pre, Walker* walker_post, int particle) = 0;
    //NOTHING TO UPDATE FOR BF
    
    virtual double get_spatial_ratio_IS(Walker* walker_post, Walker* walker_pre, int particle) = 0;
    //BF ratio is indep. of kinetics

    virtual void calculate_energy_necessities(Walker* walker) = 0;

    virtual void update_necessities_IS(Walker* walker_pre, Walker* walker_post, int particle) = 0;
    //NO BF NECESSITIES

    virtual void copy_walker_IS(Walker* parent, Walker* child) = 0;
    virtual void copy_walker_BF(Walker* parent, Walker* child) = 0;

    virtual void reset_walker_IS(Walker* walker_pre, Walker* walker_post, int particle) = 0;
    //NOTHING TO RESET FOR BF

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

    virtual void get_necessities_IS(Walker* walker);

    virtual void update_walker_IS(Walker* walker_pre, Walker* walker_post, int particle);

    virtual double get_spatial_ratio_IS(Walker* walker_post, Walker* walker_pre, int particle);
    
    virtual void calculate_energy_necessities(Walker* walker);

    virtual void update_necessities_IS(Walker* walker_pre, Walker* walker_post, int particle);

    virtual void copy_walker_IS(Walker* parent, Walker* child);
    virtual void copy_walker_BF(Walker* parent, Walker* child);

    virtual void reset_walker_IS(Walker* walker_pre, Walker* walker_post, int particle);

};

class Closed_form : public Kinetics {
public:
    Closed_form(int n_p, int dim);

    virtual double get_KE(Walker* walker);
    virtual void get_QF(Walker* walker);

    virtual void get_necessities_IS(Walker* walker);

    virtual void update_walker_IS(Walker* walker_pre, Walker* walker_post, int particle);

    virtual void calculate_energy_necessities(Walker* walker);

    virtual double get_spatial_ratio_IS(Walker* walker_post, Walker* walker_pre, int particle);
    
    virtual void update_necessities_IS(Walker* walker_pre, Walker* walker_post, int particle);

    virtual void copy_walker_IS(Walker* parent, Walker* child);
    virtual void copy_walker_BF(Walker* parent, Walker* child);

    virtual void reset_walker_IS(Walker* walker_pre, Walker* walker_post, int particle);

};

#endif	/* KINETICS_H */

