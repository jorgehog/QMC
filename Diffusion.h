/* 
 * File:   Diffusion.h
 * Author: jorgehog
 *
 * Created on 16. april 2012, 14:03
 */

#ifndef DIFFUSION_H
#define	DIFFUSION_H

class Diffusion {
protected:
    int n_p;
    int dim;

    QMC* qmc;

    double timestep;
    double D;
    long random_seed;

    double std;


public:
    Diffusion(int n_p, int dim, double timestep, long random_seed, double D);

    virtual double get_new_pos(const Walker* walker, int i, int j);

    virtual double get_g_ratio(const Walker* walker_post, const Walker* walker_pre, int particle) const = 0;

    virtual double get_GBfunc(Walker* walker_pre, Walker* walker_post, double E_T) const = 0;

    double call_RNG();

    void set_qmc_ptr(QMC* qmc) {
        this->qmc = qmc;
    }
};

class Fokker_Planck : public Diffusion {
public:
    Fokker_Planck(int n_p, int dim, double timestep, long random_seed, double D = 0.5);

    virtual double get_new_pos(const Walker* walker, int i, int j);
    virtual double get_g_ratio(const Walker* walker_post, const Walker* walker_pre, int particle) const;

    virtual double get_GBfunc(Walker* walker_pre, Walker* walker_post, double E_T) const;

};

class Simple : public Diffusion {
public:
    Simple(int n_p, int dim, double timestep, long random_seed, double D = 0.5);


    virtual double get_new_pos(const Walker* walker, int i, int j);
    virtual double get_g_ratio(const Walker* walker_post, const Walker* walker_pre, int particle) const;

    virtual double get_GBfunc(Walker* walker_pre, Walker* walker_post, double E_T) const;
};
#endif	/* DIFFUSION_H */

