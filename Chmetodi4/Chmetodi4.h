#pragma once
typedef float real;

real cir11(real* x, int n, int j, real h);

real cir12(real* x, int n, int j, real h);

real line3(real* x, int n, int j, real h);

real cir21(real* x, int n, int j, real h);


real cir22(real* x, int n, int j, real h);

real line2(real* x, int n, int j, real h);

real cir31(real* x, int n, int j, real h);

real cir32(real* x, int n, int j, real h);

real line31(real* x, int n, int j, real h);

real line32(real* x, int n, int j, real h);

real line33(real* x, int n, int j, real h);

real sinus(real* x, int n, int j, real h);

real cir11_1(real* x, int n);

real cir11_2(real* x, int n);

real cir12_1(real* x, int n);

real cir12_2(real* x, int n);

real cir21_1(real* x, int n);

real cir21_2(real* x, int n);

real cir22_1(real* x, int n);

real cir22_2(real* x, int n);

real line3_1(real* x, int n);

real line3_2(real* x, int n);

real line2_1(real* x, int n);

real line2_2(real* x, int n);

real line31_1(real* x, int n);

real line31_2(real* x, int n);

real line32_1(real* x, int n);

real line32_2(real* x, int n);

real line33_1(real* x, int n);

real line33_2(real* x, int n);

real sinus_1(real* x, int n);

real sinus_2(real* x, int n);

void CalculateJacobinum2(real** J, real* x, int n, int m);

int Newton1(int n, int m, real* x0, real eps1, real eps2, int maxiter);

void CalculateJacobi1(real** J, real* x, int n, int m);

void CalculateMinusF1(real* f, real* x, int n, int m);

int Newton2(int n, int m, real* x0, real eps1, real eps2, int maxiter);
real CalcNorm(real* x, int n);
void SolveSlae(real** A, real* b, int n);
void MatrixMult(real** A, real* x, real* b, int n);