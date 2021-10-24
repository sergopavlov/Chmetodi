#pragma once
typedef float real;
typedef float reals;

int main();

void JacobiIterationRelax(int n, int m, real** mat, real* b, real* x0, real* x, real omega);

void MatrixMult(int n, int m, real** mat, real* x, real* b);

void SolveJacobiRelax(int n, int m, real precision, int maxiter, real** mat, real* b, real* x0, real* x, real omega);

void SolveZeidelRelax(int n, int m, real precision, int maxiter, real** mat, real* b, real* x0, real omega);
