/* 
 * File:   Hamiltonian.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:53
 */

#ifndef HAMILTONIAN_H
#define	HAMILTONIAN_H

class Potential;
class Kinetics;
class Hamiltonian {
public:
    Hamiltonian();
    
    Potential pot;
    Kinetics kin;
    
    double get_coulomb(const Walker &walker);
    

private:
    bool coulomb_switch_on;
};

#endif	/* HAMILTONIAN_H */

