#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include "time.h"
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    // erklærer arrays jeg trenger, bruker dynamic memory allocation: pointer = new type[n]:
    int n = atoi(argv[1]);
    double h = 1.0/(n+1.0);
    double* a = new double[n];
    double* b = new double[n];
    double* c = new double[n];
    double* f = new double[n];
    double* u = new double[n];

    // fyller arrays a, b og c
    for (int i=0; i<n; i++) { a[i] = c[i] = -1.0; b[i] = 2.0; }

    // fyller array f
    for (int i=0; i<n; i++) {
        double x = i*h;
        f[i] = 100.0*exp(-10.0*x)*h*h;
    }

    // grensebetinger
    u[0] = u[n-1] = 0.0;

    // erklærer klokkevariabler
    clock_t start, finish;
    start = clock();

    // forward substitution
    for (int i=0; i<n; i++) {
        b[i+1] = b[i+1] - (a[i]*c[i])/b[i];
        f[i+1] = (f[i+1] - (a[i]*f[i])/b[i]);
    }

    // backward substitution
    for (int i=n-2; i>=1; i--) {
        u[i] = (f[i] - c[i]*u[i+1])/b[i];
    }

    finish = clock();
    cout << "Time elapsed: " << ((finish-start)/CLOCKS_PER_SEC) << endl;

    // skriver ut u til fil data.dat
    fstream outFile;
    outFile.open("data.dat", ios::out);

    outFile << n << endl;
    for (int i=0; i<n; i++) {
        outFile << u[i] << endl;
    }
    outFile.close();


    return 0;
}

