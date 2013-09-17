#include <armadillo>
#include <time.h>

using namespace std;
using namespace arma;

int main ()
{
    int n = 3000;
    double h = 1.0/(n+1.0);
    mat A(n,n);
    // fyller inn 2 på diagonalen
    for (int i=0; i<n; i++) {
        A(i, i) = 2;
    }
    // fyller inn -1 over og under diagonalen
    for (int i=1; i<n; i++) {
        A(i,i-1) = -1;
        A(i-1,i) = -1;
    }

    vec f(n);
    vec u(n);

    // fyller vektor f
    for (int i=0; i<n; i++) {
        double x = i*h;
        f[i] = 100.0*exp(-10.0*x)*h*h;
    }

    clock_t start, finish;
    start = clock();
    // erklærer matriser som skal brukes i LU-dekomponeringen
    mat L, U, P;
    // LU-dekomponerer A
    lu(L, U, P, A);

    // løser likn.systemet basert på L og U
    mat y = inv(L)*f;
    u = inv(U)*y;
    //cout << u << endl;

    finish = clock();
    cout << "Time elapsed: " << ((finish-start)/CLOCKS_PER_SEC) << endl;

    return 0;
}

