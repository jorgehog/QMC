/* 
 * File:   Potential.h
 * Author: jorgehog
 *
 * Created on 13. april 2012, 17:21
 */

#ifndef POTENTIAL_H
#define	POTENTIAL_H

class Potential {
public:
    Potential();
  
    virtual double get_pot_E(const Walker &walker) const = 0;
 


protected:
    int n_p;
    int dim;
    bool coulomb_on = true;

    double get_Coulomb(const Walker &walker) const;


};


class Harmonic_osc : public Potential {
protected:
    double w;

public:
    
    Harmonic_osc(int n_p, int dim, double W, bool coulomb_on);

    virtual double get_pot_E(const Walker& walker) const;

};

#endif	/* POTENTIAL_H */

