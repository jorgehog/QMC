/* 
 * File:   Diffusion.h
 * Author: jorgehog
 *
 * Created on 16. april 2012, 14:03
 */

#ifndef DIFFUSION_H
#define	DIFFUSION_H

class Diffusion {
private:
    int n_p;
    int dim;
    
    double timestep;
    double D;
    double std;
    
    
public:
    Diffusion();

    virtual bool metropolis_test() = 0;
    virtual void set_trial_pos() = 0;
    virtual void set_new_pos() = 0;
    virtual void get_new_values() = 0;
    virtual void update_walker() = 0;
    virtual void get_full_ratio() = 0;


};

class Fokker_Planck : public Diffusion {
public:
    Fokker_Planck();

    virtual bool metropolis_test();
    virtual void set_trial_pos();
    virtual void set_new_pos();
    virtual void get_new_values();
    virtual void update_walker();
    virtual void get_full_ratio();

protected:
    double test_qforce(Walker &walker);
    double get_g_ratio(const Walker &walker_new, const Walker &walker_old);


};

class Simple : public Diffusion {
public:
    Simple();

    virtual bool metropolis_test();
    virtual void set_trial_pos();
    virtual void set_new_pos();
    virtual void get_new_values();
    virtual void update_walker();
    virtual void get_full_ratio();

};
#endif	/* DIFFUSION_H */

