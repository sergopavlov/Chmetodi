#pragma once
typedef  float real;

int MSG(int* ia, int* ja, int n, real* al, real* di, real* x, real* b, int maxiter, real eps);

real DotProduct(real* x, real* y, int n);

void MatrixMult(int* ia, int* ja, int n, real* al, real* di, real* x, real* b);

void inputparams(int* n, int* m, int* maxiter, real* eps);

void input(int* ia, int* ja, real* di, real* al, real* x0, real* b, int n, int m);
