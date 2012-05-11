/* 
 * File:   QMC.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 17:42
 */

#ifndef QMC_H
#define	QMC_H

class Walker;
class Diffusion;
class Kinetics;
class Jastrow;

class QMC {
protected:
    int n_c;

    int n_p;
    int n2;
    int dim;

    long random_seed;

    Jastrow jastrow;
    Diffusion diffusion;
    System system;
    Kinetics kinetics;

    QMC();

    virtual void run_method() = 0;

    virtual void initialize() = 0;

    virtual void output() = 0;

    void get_gradients(Walker& walker, int particle);
    void get_gradients(Walker& walker);
    void get_wf_value(Walker& walker);

    void calc_for_diffused_walker(Walker &walker_prediff, Walker &walker_postdiff, int particle);


};

class VMC : public QMC {
protected:
    bool dist_to_file;

    virtual void initialize();

public:

    VMC(int n_p, int dim, int n_c, long random_seed, Jastrow jastrow,
            Diffusion diffusion, System system, Kinetics kinetics);


    Walker wfold;
    Walker wfnew;

    virtual void run_method();
    virtual void output();

};

class DMC : public QMC {
protected:

    int n_w_orig;

    virtual void initialize();
    void increase_walker_space();
    void calc_gs_statistics();
    void bury_the_dead();
    void Evolve_walker(int k);

    //void copy_walker(int parent, int child); ASSIGNMENT OPERATOR. NB: CHECK SIZE
    //bool singular(int k); MAKE WALKER METHOD

    //virtual void update_pos(int k) = 0; THIS IS DIFFUSION

    //problem: DMC not equal for IMPORTANCE vs. BF


public:
    DMC();

    Walker **Angry_mob;

    virtual void run_method();

    virtual void output();
};



#endif	/* QMC_H */