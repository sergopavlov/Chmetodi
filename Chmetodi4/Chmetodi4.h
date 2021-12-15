#pragma once
typedef float real;

real f1(real* x, int n);

real f2(real* x, int n);

int Newton(int n, int m, real* x0, real eps1, real eps2, int maxiter);
real CalcNorm(real* x, int n);
void SolveSlae(real** A, real* b, int n);
void MatrixMult(real** A, real* x, real* b, int n);