#pragma once
typedef float real;

real quickpower(real x, int n);

int SolveZeidelRelax(int n, int m, real precision, int maxiter, real** mat, real* b, real* x0, real omega);