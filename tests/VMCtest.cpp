/* 
 * File:   newsimpletest1.cpp
 * Author: jorgehog
 *
 * Created on 22.jun.2012, 12:52:55
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

#include <stdlib.h>
#include <iostream>

#include "lib.h"

/*
 * Simple C++ Test Suite
 */

void test_nocol_nojast() {
    int n_p, dim, n_c;
    double alpha, w, dt, h;
    long random_seed;
    double var, E;

    dim = 2;
    n_c = 10000;
    alpha = 1;

    int* NP = new int[3];
    double* W = new double[2];
    W[0] = 1.0;
    W[1] = 0.5;
    NP[0] = 2;
    NP[1] = 6;
    NP[2] = 12;

    Orbitals* HO_basis;

    Potential* HO_pot;

    Jastrow* jastrow;

    Kinetics* kinetics;

    System* Quantum_Dots;

    Sampling* sample_method;

    VMC* vmc;

    dt = 0.5;

    h = 0.001;

    random_seed = -time(NULL);


    std::cout << "Numerical" << std::endl;
    bool success = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {

            n_p = NP[i];
            w = W[j];

            HO_basis = new oscillator_basis_HC(n_p, dim, alpha, w);

            HO_pot = new Harmonic_osc(n_p, dim, w, false);
            jastrow = new No_Jastrow();

            kinetics = new Numerical(n_p, dim, h);

            Quantum_Dots = new Fermions(n_p, dim, HO_pot, HO_basis);

            sample_method = new Brute_Force(n_p, dim, dt, random_seed);

            vmc = new VMC(n_p, dim, n_c, jastrow, sample_method, Quantum_Dots, kinetics);

            vmc->run_method();

            var = vmc->get_var();
            E = vmc->get_energy();

            if ((E = 1. / 3 * (i + 1)*(i + 2)*(2 * i + 1) * w) && (var < 10E-5)) {
                std::cout << "n_p=" << n_p << " w=" << w << " success" << std::endl;
                std::cout << E << "\t" << var << std::endl;
                std::cout << endl;
            } else {
                std::cout << "n_p=" << n_p << " w=" << w << "failed" << std::endl;
                std::cout << E << "\t" << var << std::endl;
                std::cout << endl;
                success = false;
            }

        }

    }


    if (success == false) {
        std::cout << "%TEST_FAILED% time=0 testname=no_col_no_jast (nocolnojast_test) message=test failed" << std::endl;
    }
}

//void testlol() {
//    std::cout << "whatever?" << std::endl;
//    std::cout << "%TEST_FAILED% time=0 testname=testlol (lollertest) message=FAIL TROLOL" << std::endl;
//}

void test_col_jast_num() {
    int n_p, dim, n_c;
    double alpha, beta, w, dt, h;
    long random_seed;
    double var, E;

    dim = 2;
    n_c = 10000;

    int* NP = new int[3];
    double* W = new double[2];
    double** E_ref = new_matrix(3, 2);
    E_ref[0][0] = 3.0;
    E_ref[0][1] = 1.66;
    E_ref[1][0] = 20.19;
    E_ref[1][1] = 11.81;
    E_ref[2][0] = 65.79;
    E_ref[2][1] = 39.23;
    
    W[0] = 1.0;
    W[1] = 0.5;
    NP[0] = 2;
    NP[1] = 6;
    NP[2] = 12;

    Orbitals* HO_basis;

    Potential* HO_pot;

    Jastrow* jastrow;

    Kinetics* kinetics;

    System* Quantum_Dots;

    Sampling* sample_method;

    VMC* vmc;


    h = 0.001;

    random_seed = -time(NULL);


    std::cout << "Numerical" << std::endl;
    bool success = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {

            n_p = NP[i];
            w = W[j];
            
            initVMC(n_p, dim, w, dt, "QDots", alpha, beta);

            HO_basis = new oscillator_basis_HC(n_p, dim, alpha, w);

            HO_pot = new Harmonic_osc(n_p, dim, w);
            jastrow = new Pade_Jastrow(n_p, dim, beta);

            kinetics = new Numerical(n_p, dim, h);

            Quantum_Dots = new Fermions(n_p, dim, HO_pot, HO_basis);

            sample_method = new Brute_Force(n_p, dim, dt, random_seed);

            vmc = new VMC(n_p, dim, n_c, jastrow, sample_method, Quantum_Dots, kinetics);

            vmc->run_method();

            var = vmc->get_var();
            E = vmc->get_energy();

            if ((E-E_ref[i][j])*(E-E_ref[i][j]) < 0.5*n_p) {
                std::cout << "n_p=" << n_p << " w=" << w << " success" << std::endl;
                std::cout << E << "\t" << E_ref[i][j]<< std::endl;
                std::cout << endl;
            } else {
                std::cout << "n_p=" << n_p << " w=" << w << "failed" << std::endl;
                std::cout << E << "\t" << E_ref[i][j]<< std::endl;
                std::cout << endl;
                success = false;
            }

        }

    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% VMCtest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% no_col_no_jast (nocolnojast_test)" << std::endl;
    test_nocol_nojast();
    std::cout << "%TEST_FINISHED% time=0 no_col_no_jast (nocolnojast_test)" << std::endl;

    std::cout << "%TEST_STARTED% test_col_jast_num (coljastnum_test)" << std::endl;
    test_col_jast_num();
    std::cout << "%TEST_FINISHED% time=0 test_col_jast_num (coljastnum_test)" << std::endl;

    //    std::cout << "%TEST_STARTED% testlol (lollertest)\n" << std::endl;
    //    testlol();
    //    std::cout << "%TEST_FINISHED% time=0 testlol (lollertest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

