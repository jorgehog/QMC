/* 
 * File:   Orbitals_old.cpp
 * Author: Jørgen
 * 
 * Created on 13. april 2012, 22:33
 */

#include "QMCheaders.h"

Orbitals_old::Orbitals_old(int n_p, int dim) {
    this->n_p = n_p;
    this->dim = dim;
}

oscillator_basis_HC::oscillator_basis_HC(int n_p, int dim, double alpha, double w)
: Orbitals_old(n_p, dim) {

    this->alpha = alpha;
    this->w = w;
}


double oscillator_basis_HC::phi(const Walker* walker, int particle, int q_num) const{
    double r2, H, x, y;

    r2 = walker->get_r_i2(particle);
    x = walker->r(particle,0);
    y = walker->r(particle,1);


    if (q_num == 0) {
        H = 1;
    } else if (q_num == 1) {
        H = 2 * x;
    } else if (q_num == 2) {
        H = 2 * y;
    } else if (q_num == 3) {
        H = 4 * x * x - 2;
    } else if (q_num == 4) {
        H = 4 * y * y - 2;
    } else if (q_num == 5) {
        H = 4 * x*y;
    } else if (q_num == 6) {
        H = 4 * x * (2 * y * y - 1);
    } else if (q_num == 7) {
        H = 4 * y * (2 * x * x - 1);
    } else if (q_num == 8) {
        H = 8 * y * y * y - 12 * y;
    } else if (q_num == 9) {
        H = 8 * x * x * x - 12 * x;
    } else if (q_num == 10) {
        H = 8 * y * x * (2 * x * x - 3);
    } else if (q_num == 11) {
        H = 8 * y * x * (2 * y * y - 3);
    } else if (q_num == 12) {
        H = 16 * y * y * (y * y - 3) + 12;
    } else if (q_num == 13) {
        H = 16 * x * x * (x * x - 3) + 12;
    } else if (q_num == 14) {
        H = 4 * (2 * x * x - 1)*(2 * y * y - 1);
    } else {
        std::cout << "Mismatching quantum number: " << q_num << std::endl;
    }

    return H * exp(-0.5 * alpha * w * r2);
}

double oscillator_basis_HC::del_phi(const Walker* walker, int particle, int q_num, int d) const{
    double r2, H, x, y;

    r2 = walker->get_r_i2(particle);

    x = walker->r(particle,0);
    y = walker->r(particle,1);


    //Hermite polynomials (up to 4)
    if (q_num == 0) {
        H = -w * alpha * walker->r(particle,d);
    } else if (q_num == 1) {
        if (d == 0) {
            H = 2 * (1 - alpha * w * x * x);
        } else {
            H = -2 * alpha * w * x*y;
        }
    } else if (q_num == 2) {
        if (d == 0) {
            H = -2 * alpha * w * y*x;
        } else {
            H = 2 * (1 - alpha * w * y * y);
        }

    } else if (q_num == 3) {
        if (d == 0) {
            H = 2 * x * (4 + alpha * w - 2 * x * x * alpha * w);
        } else {
            H = (4 * x * x - 2)*(-alpha * w * y);
        }
    } else if (q_num == 4) {
        if (d == 0) {
            H = (4 * y * y - 2)*(-alpha * w * x);
        } else {
            H = 2 * y * (4 + alpha * w - 2 * y * y * alpha * w);
        }
    } else if (q_num == 5) {
        if (d == 0) {
            H = 4 * y - 4 * x * x * y * w*alpha;
        } else {
            H = 4 * x - 4 * x * y * y * w*alpha;
        }
    } else if (q_num == 6) {
        if (d == 0) {
            H = -4 * (-1 + alpha * w * x * x)*(-1 + 2 * y * y);
        } else {
            H = -4 * x * y * (alpha * w * (2 * y * y - 1) - 4);
        }
    } else if (q_num == 7) {
        if (d == 0) {
            H = -4 * x * y * (alpha * w * (2 * x * x - 1) - 4);
        } else {
            H = -4 * (-1 + alpha * w * y * y)*(-1 + 2 * x * x);
        }
    } else if (q_num == 8) {
        if (d == 0) {
            H = 4 * alpha * w * y * (3 - 2 * y * y) * x;
        } else {
            H = 4 * (y * y * (alpha * w * (3 - 2 * y * y) + 6) - 3);
        }
    } else if (q_num == 9) {
        if (d == 0) {
            H = 4 * (x * x * (alpha * w * (3 - 2 * x * x) + 6) - 3);
        } else {
            H = 4 * alpha * w * x * (3 - 2 * x * x) * y;
        }
    } else if (q_num == 10) {
        if (d == 0) {
            H = -8 * y * (alpha * w * x * x * (2 * x * x - 3) - 3 * (2 * x * x - 1));
        } else {
            H = -8 * x * (2 * x * x - 3)*(alpha * w * y * y - 1);
        }
    } else if (q_num == 11) {
        if (d == 0) {
            H = -8 * y * (2 * y * y - 3)*(alpha * w * x * x - 1);
        } else {
            H = -8 * x * (alpha * w * y * y * (2 * y * y - 3) - 3 * (2 * y * y - 1));
        }
    } else if (q_num == 12) {
        if (d == 0) {
            H = -4 * alpha * w * x * (4 * y * y * y * y - 12 * y * y + 3);
        } else {
            H = -4 * y * (3 * (alpha * w + 8) + 4 * alpha * w * y * y * y * y - 4 * y * y * (3 * alpha * w + 4));
        }
    } else if (q_num == 13) {
        if (d == 0) {
            H = -4 * x * (3 * (alpha * w + 8) + 4 * alpha * w * x * x * x * x - 4 * x * x * (3 * alpha * w + 4));
        } else {
            H = -4 * alpha * w * y * (4 * x * x * x * x - 12 * x * x + 3);
        }
    } else if (q_num == 14) {
        if (d == 0) {
            H = -4 * x * (2 * y * y - 1)*(alpha * w * (2 * x * x - 1) - 4);
        } else {
            H = -4 * y * (2 * x * x - 1)*(alpha * w * (2 * y * y - 1) - 4);
        }
    } else {
        std::cout << "Mismatching quantum number: " << q_num << std::endl;
    }

    return H * exp(-0.5 * alpha * w * r2);
}

double oscillator_basis_HC::lapl_phi(const Walker* walker, int particle, int q_num) const {
    double r2, H, x, y, aw2;

    r2 = walker->get_r_i2(particle);
    x = walker->r(particle,0);
    y = walker->r(particle,1);
    aw2 = alpha * alpha * w * w;


    //Hermite polynomials (up to 4)
    if (q_num == 0) {
        H = w * alpha * (w * alpha * r2 - dim);
    } else if (q_num == 1) {
        H = 2 * x * w * alpha * (w * alpha * r2 - 4);
    } else if (q_num == 2) {
        H = 2 * y * w * alpha * (w * alpha * r2 - 4);
    } else if (q_num == 3) {
        H = 2 * (4 + w * alpha * (2 - 12 * x * x + w * alpha * r2 * (2 * x * x - 1)));
    } else if (q_num == 4) {
        H = 2 * (4 + w * alpha * (2 - 12 * y * y + w * alpha * r2 * (2 * y * y - 1)));
    } else if (q_num == 5) {
        H = 4 * alpha * w * x * y * (alpha * w * r2 - 6);
    } else if (q_num == 6) {
        H = 4 * x * (aw2 * r2 * (2 * y * y - 1) + 4 * alpha * w * (1 - 4 * y * y) + 4);
    } else if (q_num == 7) {
        H = 4 * y * (aw2 * r2 * (2 * x * x - 1) + 4 * alpha * w * (1 - 4 * x * x) + 4);
    } else if (q_num == 8) {
        H = 4 * y * (aw2 * r2 * (2 * y * y - 3) + 4 * alpha * w * (3 - 4 * y * y) + 12);
    } else if (q_num == 9) {
        H = 4 * x * (aw2 * r2 * (2 * x * x - 3) + 4 * alpha * w * (3 - 4 * x * x) + 12);
    } else if (q_num == 10) {
        H = 8 * x * y * (aw2 * r2 * (2 * x * x - 3) + 2 * alpha * w * (9 - 10 * x * x) + 12);
    } else if (q_num == 11) {
        H = 8 * x * y * (aw2 * r2 * (2 * y * y - 3) + 2 * alpha * w * (9 - 10 * y * y) + 12);
    } else if (q_num == 12) {
        H = 4 * (aw2 * r2 * (3 + 4 * y * y * (y * y - 3)) + 2 * alpha * w * (36 * y * y - 3 - 20 * y * y * y * y) + 24 * (y * y - 1));
    } else if (q_num == 13) {
        H = 4 * (aw2 * r2 * (3 + 4 * x * x * (x * x - 3)) + 2 * alpha * w * (36 * x * x - 3 - 20 * x * x * x * x) + 24 * (x * x - 1));
    } else if (q_num == 14) {
        H = 4 * (aw2 * r2 * (4 * x * x * y * y + 1 + 2 * r2) - 2 * alpha * w * (1 + 6 * r2 + 20 * x * x * y * y) + 8 * (r2 + 1));
    } else {
        std::cout << "Mismatching quantum number: " << q_num << std::endl;
    }

    return H * exp(-0.5 * alpha * w * r2);
}
