/* 
 * File:   Walker.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:50
 */

#ifndef WALKER_H
#define	WALKER_H


class Walker {
protected:
    int n_p;
    int n2;
    int dim;
    
public:
  
    Walker(int n_p, int dim);
  
    double ratio;
    double value;
    double lapl_sum;
    
    double** r;
    double** r_rel;

    double** qforce;
    
    double** spatial_grad;
    double** jast_grad;
    double** inv;
    
    double get_r_i2(int i) const;
    
    double abs_relative(int i, int j);

    void make_rel_matrix();
    
    bool is_singular();

};