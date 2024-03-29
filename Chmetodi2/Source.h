#pragma once
typedef float real;
typedef float reals;


void JacobiIterationRelax(int n, int m, real** mat, real* b, real* x0, real* x, real omega);

void MatrixMult(int n, int m, real** mat, real* x, real* b);

int SolveJacobiRelax(int n, int m, real precision, int maxiter, real** mat, real* b, real* x0, real* x, real omega);

int SolveZeidelRelax(int n, int m, real precision, int maxiter, real** mat, real* b, real* x0, real omega);
