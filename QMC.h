/* 
 * File:   QMC.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 17:42
 */

#ifndef QMC_H
#define	QMC_H

class Hamiltonian;
class QMC {
protected:
    int n_c;

    Wavefunction wf_old;
    Wavefunction wf_new;
    Hamiltonian H;
    
    int n_p;
    int n2;
    int dim;

    double delta_e;
    double local_e;
    double local_e2;
    double std;

    long random_seed;
    bool map_wf;


    bool metropolis_test();
    void output();
    virtual void do_vmc() = 0;
    
    virtual void set_trial_pos() = 0;
    virtual void set_new_pos() = 0;
    virtual void get_full_ratio() = 0;
    virtual void update_walker() = 0;

};

class Importance : public QMC {
public:
    int moved_particle;
    double timestep;
    double sqrt_timestep;
    double D;



    Importance(int N_C, int N_P, int DIM, double TIMESTEP);


    double test_qforce();
    double get_g_ratio();


    virtual void set_trial_pos();

    virtual void do_vmc();
    virtual void set_new_pos();

    virtual void get_full_ratio();
    virtual void update_walker();



};

class Brute_Force : public QMC {
public:
    double steplength;

    Brute_Force(int N_C, int N_P, int DIM, double STEPLENGTH);

    virtual void set_trial_pos(Wavefunction &wf, System &system, Jastrow_factor &jastrow, Kinetics &kinetics);

    virtual void do_vmc(Potential &pot, Kinetics &kinetics, System &system, Jastrow_factor &jastrow,
            Wavefunction &wf_old, Wavefunction &wf_new);
    virtual void set_new_pos(const Wavefunction &wf_old, Wavefunction &wf_new);

    virtual void get_full_ratio(Wavefunction &wf_new, Wavefunction &wf_old, Jastrow_factor &jastrow);
    virtual void update_walker(Wavefunction &wf_old, Wavefunction &wf_new, System &system, Kinetics &kinetics);

};

