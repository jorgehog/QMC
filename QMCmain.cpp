/* 
 * File:   QMCmain.cpp
 * Author: jorgehog
 *
 * Created on 13. april 2012, 17:04
 */

//#include "mpi.h"
#include "QMCheaders.h"

#include <sys/time.h>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int n_p, dim, n_c, numprocs, my_rank;
    double alpha, beta, w, dt, h, cumul_e, cumul_e2, e, e2, E_T;
    long random_seed;

    //initializing MPI
    //    MPI_Init(&argc, &argv);
    //    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    //    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    random_seed = -1.234; //-time(NULL);
    //    random_seed = -time(NULL) - my_rank;

    n_p = 2;
    dim = 2;
    w = 1;

    n_c = 1000000;

    bool vmc = false;
    bool dmc = true;

    string system = "QDots";
    string sampling = "BF";
    string kinetics_type = "Num";

    bool dist_out = false;
    bool dist_in = true;

    bool use_jastrow = true;
    bool use_coulomb = true;


    initVMC(n_p, dim, w, dt, system, sampling, alpha, beta);
    //cout << alpha << " " << beta << endl;
    if ((use_jastrow == false) && (use_coulomb == false)) {
        alpha = 1;
    }
    
    if (dmc){
        dt = 0.005;
    }


    Kinetics* kinetics;
    Orbitals* SP_basis;
    Potential* onebody_pot;
    System* SYSTEM;
    Sampling* sample_method;
    Jastrow* jastrow;

    if (kinetics_type == "Num") {
        h = 0.0001;
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
        SP_basis = new oscillator_basis(n_p, dim, alpha, w);

        onebody_pot = new Harmonic_osc(n_p, dim, w, use_coulomb);

        SYSTEM = new Fermions(n_p, dim, onebody_pot, SP_basis);

    } else {
        cout << "unknown system" << endl;
        exit(1);
    }




    if (vmc) {
        VMC* vmc = new VMC(n_p, dim, n_c, jastrow, sample_method, SYSTEM, kinetics, dist_out);

        vmc->run_method();


        //    cumul_e = cumul_e2 = 0;
        //    e = vmc->get_energy();
        //    e2 = vmc->get_e2();
        //    
        //    MPI_Reduce(&e, &cumul_e, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        //    MPI_Reduce(&e2, &cumul_e2, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        //
        //    if (my_rank == 0) {
        //        vmc->set_e(e);
        //        vmc->set_e2(e2);
        //        
        //        vmc->output();
        //    }
        vmc->output();
        if (dmc) {
            E_T = vmc->get_energy();
        }
    }

    if (dmc) {

        int n_w = 1000;
        if (!vmc) {
            E_T = 3.00031;
        }
        

        DMC* dmc = new DMC(n_p, dim, n_w, n_c, E_T, jastrow, sample_method, SYSTEM, kinetics, dist_in);
        dmc->run_method();
        dmc->output();
    }



    //    MPI_Finalize();
    return 0;
}

