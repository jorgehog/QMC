/* 
 * File:   Walker.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:50
 */

#ifndef WALKER_H
#define	WALKER_H

#include <armadillo>

using namespace arma;

class Walker {
protected:
    int n_p;
    int n2;
    int dim;
    
public:
  
    Walker(int n_p, int dim);
  
    double slater_ratio;
    double value;
    double lapl_sum;
    
    mat r;
    mat r_rel;

    mat qforce;
    
    mat spatial_grad;
    mat jast_grad;
    mat inv;
    
    double get_r_i2(int i) const;
    
    double abs_relative(int i, int j);

    void make_rel_matrix();
    
    bool is_singular();
    
    bool check_bad_qforce();

};

#endif	/* WALKER_H */
