/* 
 * File:   QMCmain.cpp
 * Author: jorgehog
 *
 * Created on 13. april 2012, 17:04
 */

#include "Diffusion.h"
#include "Jastrow.h"
#include "Kinetics.h"
#include "Orbitals.h"
#include "Potential.h"
#include "QMC.h"
#include "Sampling.h"
#include "System.h"
#include "Walker.h"
#include <sys/time.h>

#include "QMCInitializer.h"
#include <iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int n_p, dim, n_c;
    double alpha, beta, w, dt, h;
    long random_seed;

    n_p = 2;
    dim = 2;
    w = 1.0;

    n_c = 100000;

    initVMC(n_p, dim, w, dt, "QDots", alpha, beta);

    h = 0.001;

    random_seed = -time(NULL);


    Orbitals* HO_basis = new oscillator_basis_HC(n_p, dim, alpha, w);

    Potential* HO_pot = new Harmonic_osc(n_p, dim, w);

    Jastrow* jastrow = new Pade_Jastrow(n_p, dim, beta);
    //Jastrow* jastrow = new No_Jastrow();

    Kinetics* kinetics = new Numerical(n_p, dim, h);

    System* Quantum_Dots = new Fermions(n_p, dim, HO_pot, HO_basis);

    Sampling* sample_method = new Importance(n_p, dim, dt, random_seed);

    QMC* vmc = new VMC(n_p, dim, n_c, jastrow, sample_method, Quantum_Dots, kinetics);

    vmc->run_method();
    vmc->output();

    return 0;
}

