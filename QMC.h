/* 
 * File:   QMC.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 17:42
 */

#ifndef QMC_H
#define	QMC_H

class Walker;
class QMC {
protected:
    int n_c;
    
    int n_p;
    int n2;
    int dim;
    
    double std;
    long random_seed;

    Jastrow jastrow;
    Sampling sampling;
    
    
    virtual void run_method() = 0;
    
    virtual void set_trial_pos() = 0;
    virtual void set_new_pos() = 0;
    virtual void get_full_ratio() = 0;

};

class VMC: public QMC {
protected:
    bool dist_to_file;

public:
    VMC();
    virtual void run_method();
    
 
};



#endif	/* QMC_H */