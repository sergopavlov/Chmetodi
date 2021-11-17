#pragma once
typedef float real;
typedef float reals;

void Solve(real* Al, real* Di, int* Ia, int* D, int n, real* b);

void LDLT(real* Al, real* Di, int* Ia, int* D, int n);

void GaussL(real* Al, real* Di, int* Ia, int* D, int n, real* b);

void GaussD(int* D, int n, real* b);

void GaussLT(real* Al, real* Di, int* Ia, int* D, int n, real* b);

void MatrixMult(real* Al, real* Di, int* Ia, int n, real* y, real* x);


void Gauss(real** A, int n, real* x, real* b);

void Multmatr(real** A, real* x, real* b, int n);


void MatrixMultL(real* Al, real* Di, int* Ia, int n, real* y, real* x);

void MatrixMultU(real* Al, real* Di, int* Ia, int n, real* y, real* x);


void GenegateGilbert(real* Al, real* Di, int* Ia, int n);

