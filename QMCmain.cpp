/* 
 * File:   QMCmain.cpp
 * Author: jorgehog
 *
 * Created on 13. april 2012, 17:04
 */

#include <cstdlib>
using namespace std;

double testfunc(int a, int b = 3){
    return a*b;
}

/*
 * 
 */
int main(int argc, char** argv) {
    int b;
    int c = testfunc(1);
    int d = testfunc(2, 4);
    int e = testfunc(1,b=7);
    
    cout << c << " " << d << " " << e << endl;
    cout << "3 8 7" << endl;
    
    
    return 0;
}

