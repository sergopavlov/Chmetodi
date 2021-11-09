#pragma once
typedef float real;

void input(real* Al, real* Di, real* b, int* Ia, int n, int m);

void MatrixMult(int n, int* ia, real* di, real* au, real* al, real* x, real* b);

real GetMaxEugenValue(int n, int* ia, real* di, real* au, real* al);
