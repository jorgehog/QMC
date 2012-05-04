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

    Walker wfplus;
    Walker wfminus;

public:
    Numerical(int n_p, int dim, double h = 0.0001);

    virtual double get_KE(Walker &walker, System &system);
    virtual void get_QF(Walker &walker, System &system);

};

class Closed_form : public Kinetics {
public:
    Closed_form(int n_p, int dim);

    virtual double get_KE(Walker &walker, System &system);
    virtual void get_QF(Walker &walker, System &system);

};

#endif	/* KINETICS_H */

