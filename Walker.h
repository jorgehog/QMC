/* 
 * File:   Walker.h
 * Author: jorgehog
 *
 * Created on 30. mars 2012, 16:50
 */

#ifndef WALKER_H
#define	WALKER_H

class System;
class Walker {
protected:
    int n_p;
    int n2;
    int dim;

    double** r;
    double** r_rel;

    double** qforce;

    double** spatial_grad;
    double** jast_grad;
    double** inv;
    
    Jastrow jastrow;
    
    
public:
    double get_r_i2(int i) const;
    double abs_relative(int i, int j);

    void make_rel_matrix();
    
    bool is_singular();


};