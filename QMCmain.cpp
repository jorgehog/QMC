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

    random_seed = -time(NULL);

    n_p = 6;
    dim = 2;
    w = 1;

    n_c = 100000;



    string system = "QDots";
    string sampling = "IS";
    string kinetics_type = "Num";

    bool use_jastrow = true;
    bool use_coulomb = true;




    initVMC(n_p, dim, w, dt, system, sampling, alpha, beta);

    if ((use_jastrow == false) && (use_coulomb == false)) {
        alpha = 1;
    }


    Kinetics* kinetics;
    Orbitals* SP_basis;
    Potential* onebody_pot;
    System* SYSTEM;
    Sampling* sample_method;
    Jastrow* jastrow;

    if (kinetics_type == "Num") {
        h = 0.00001;
        kinetics = new Numerical(n_p, dim, h);
    } else if (kinetics_type == "CF") {
        kinetics = new Closed_form(n_p, dim);
    } else {
        cout << "unknown kinetics" << endl;
        exit(1);
    }

    if (sampling == "IS") {
        sample_method = new Importance(n_p, dim, dt, random_seed);
    } else if (sampling == "BF") {
        sample_method = new Brute_Force(n_p, dim, dt, random_seed);
    } else {
        cout << "unknown sampling method" << endl;
        exit(1);
    }

    if (use_jastrow) {
        jastrow = new Pade_Jastrow(n_p, dim, beta);
    } else {
        jastrow = new No_Jastrow();
    }

    if (system == "QDots") {
        SP_basis = new oscillator_basis_HC(n_p, dim, alpha, w);

        onebody_pot = new Harmonic_osc(n_p, dim, w, use_coulomb);

        SYSTEM = new Fermions(n_p, dim, onebody_pot, SP_basis);

    } else {
        cout << "unknown system" << endl;
        exit(1);
    }





    QMC* vmc = new VMC(n_p, dim, n_c, jastrow, sample_method, SYSTEM, kinetics);

    vmc->run_method();
    vmc->output();

    return 0;
}

