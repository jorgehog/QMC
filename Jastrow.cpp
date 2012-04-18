/* 
 * File:   Jastrow.cpp
 * Author: jorgehog
 * 
 * Created on 30. mars 2012, 16:52
 */

#include "Jastrow.h"
#include "Walker.h"

Jastrow::Jastrow() {

}

No_Jastrow::No_Jastrow() {

}

Pade_Jastrow::Pade_Jastrow(int n_p, int dim, double beta) {
    this->n_p = n_p;
    this->n2 = n_p / 2;
    this->dim = dim;
    this->beta = beta;
}


//check when a_sym values are 1/2. 1/3 etc. Can these be retrieved from dimention?
void Pade_Jastrow::initialize(const System& system) const {
    int i, j;

    for (i = 0; i < n_p; i++) {
        for (j = 0; j < n_p; j++) {

            if ((j < n2 && i < n2) || (j >= n2 && i >= n2)) {
                a[i][j] = system.a_sym;
            } else {
                a[i][j] = system.a_asym;
            }
        }
    }
}



