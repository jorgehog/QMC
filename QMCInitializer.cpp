#include <iostream>
using namespace std;

//TMP FUNC. WILL BE PYTHON SCRIPTED

void initVMC(int n_p, int dim, double w, double &dt, std::string type, double &alpha, double &beta) {
    dt = 0.5;
    if ((dim == 2) && (type == "QDots")) {
        if (n_p = 2) {
            if (w == 1.0) {
                alpha = 0.987;
                beta = 0.398;
            } else if (w == 0.5) {
                alpha = 0.9826;
                beta = 0.3098;
            } else if (w == 0.28) {
                alpha = 0.9806;
                beta = 0.2483;
            } else if (w == 0.01) {
                alpha = 0.824;
                beta = 0.081;
            } else {
                cout << "No saved parameters for (n_p, w) = " << n_p << " " << w << endl;
            }
        } else if (n_p == 6) {
            if (w == 1.0) {
                alpha = 0.92;
                beta = 0.565;
            } else if (w == 0.5) {
                alpha = 0.9004;
                beta = 0.4099;
            } else if (w == 0.28) {
                alpha = 0.88;
                beta = 0.33;
            } else if (w == 0.01) {
                alpha = 0.64;
                beta = 0.09;
            } else {
                cout << "No saved parameters for (n_p, w) = " << n_p << " " << w << endl;
            }
        } else if (n_p == 12) {
            if (w == 1.0) {
                alpha = 0.87;
                beta = 0.68;
            } else if (w == 0.5) {
                alpha = 0.8453;
                beta = 0.4813;
            } else if (w == 0.28) {
                alpha = 0.8662;
                beta = 0.3346;
            } else if (w == 0.01) {
                alpha = 0.37;
                beta = 0.55;
            } else {
                cout << "No saved parameters for (n_p, w) = " << n_p << " " << w << endl;
            }
        } else if (n_p == 20) {
            if (w == 1) {
                alpha = 0.84;
                beta = 0.76;
            } else {
                //            alpha = 0.87;
                //            beta = 0.68;
                //            cout << "warning" << endl;
                cout << "No saved parameters for (n_p, w) = " << n_p << " " << w << endl;

            }

        } else if (n_p == 30) {
            if (w == 1) {
                alpha = 0.78;
                beta = 0.85;
            } else {
                //            alpha = 0.87;
                //            beta = 0.68;
                //            cout << "warning" << endl;
                cout << "No saved parameters for (n_p, w) = " << n_p << " " << w << endl;

            }
        } else {
            cout << "No saved parameters for n_p=" << n_p << endl;
        }
    } else {
        cout << "Unknown type " << type << "with dim=" << dim << endl;
    }
}

