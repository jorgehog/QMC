/* 
 * File:   Kinetics.h
 * Author: jorgehog
 *
 * Created on 13. april 2012, 17:45
 */

#ifndef KINETICS_H
#define	KINETICS_H


class Walker;
class Kinetics {
public:
    Kinetics();

    virtual double get_KE(Walker &walker, System &system) = 0;
    virtual void get_QF(Walker &walker, System &system) = 0;

protected:
    int n_p;
    int dim;

    bool closed_form;


};

class Numerical : public Kinetics {
protected:
    double h, h2;

public:
    Kinetics_num(QMC &qmc);
    Kinetics_num(QMC &qmc, double H);

    Walker wfplus;
    Walker wfminus;

    virtual double get_KE(Walker &walker, System &system);
    virtual void get_QF(Walker &walker, System &system);


};


class Closed_form : public Kinetics {
public:
    Kinetics_cf(VMC &vmc);

    virtual double get_KE(Walker &walker, System &system);
    virtual void get_QF(Walker &walker, System &system);

};

#endif	/* KINETICS_H */

