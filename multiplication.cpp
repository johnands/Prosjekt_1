#include "lib.h"
#include <iostream>
#include <time.h>
#include <armadillo>

using namespace std;
using namespace arma;

int main ()
{
    int n = 1000;
    // seeds
    long int n1 = 4;
    long int n2 = 5;

    // dynamic memory allocation for matrise
    // erklærer først en dobbel pointer ** (pointer som peker mot pointer) som inneholder adressen til
    // første element av en array av pointere med lengde n
    double** B = new double*[n];
    double** C = new double*[n];
    double** A = new double*[n];
    // deretter dereferencer jeg B og C ved B[i] og C[i], altså tilegner jeg verdier til arrayen av pointere, dvs. at hver
    // pointer i arrayen får en adresse i minnet som peker mot en verdi i matrisen
    for (int i=0; i<n; i++) {
        B[i] = new double[n];
        C[i] = new double[n];
        A[i] = new double[n];
    }


    // fyller matrisene B og C med random tall
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            B[i][j] = ran0(&n1);
            C[i][j] = ran0(&n2);
        }
    }

    clock_t start, finish;
    start = clock();

    // matrix multiplication manually
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            for (int k=0; k<n; k++) {
                A[i][j] += B[i][k] * C[k][j];
            }
        }
    }

    finish = clock();
    cout << "Time elapsed manually: " << ((finish-start)/CLOCKS_PER_SEC) << endl;



    // matrix multiplication with armadillo
    mat D = randu<mat>(n,n);
    mat E = randu<mat>(n,n);

    start = clock();
    mat F = D*E;

    finish = clock();
    cout << "Time elapsed armadillo: " << ((finish-start)/CLOCKS_PER_SEC) << endl;


    return 0;
}
