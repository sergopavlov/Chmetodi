#pragma once
typedef float real;

real f1(real* x, int n);

real f2(real* x, int n);

real f3(real* x, int n);

real f11(real* x, int n);

real f12(real* x, int n);

real f21(real* x, int n);

real f22(real* x, int n);

real f31(real* x, int n);

real f32(real* x, int n);

int Newton1(int n, int m, real* x0, real eps1, real eps2, int maxiter);

void CalculateJacobi1(real** J, real* x, int n, int m);

void CalculateMinusF1(real* f, real* x, int n, int m);

int Newton2(int n, int m, real* x0, real eps1, real eps2, int maxiter);
real CalcNorm(real* x, int n);
void SolveSlae(real** A, real* b, int n);
void MatrixMult(real** A, real* x, real* b, int n);