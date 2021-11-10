#pragma once
typedef float real;

void input(real* Al, real* Di, real* b, int* Ia, int n, int m);

void MatrixMult(int n, int* ia, real* di, real* au, real* al, real* x, real* b);

void LUfactorization(int n, int* ia, real* di, real* au, real* al);

void GaussU(real* au, real* di, int* ia, int n, real* b);

void GaussL(real* al, real* di, int* ia, int n, real* b);

real GetMinEugenvalue(int n, int* ia, real* di, real* au, real* al);

real GetMaxEugenValue(int n, int* ia, real* di, real* au, real* al);
