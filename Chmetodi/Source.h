#pragma once
typedef float real;
void Solve(real* Al, real* Di, int* Ia, int* D, int n, real* b);

void LDLT(real* Al, real* Di, int* Ia, int* D, int n);

void GaussL(real* Al, real* Di, int* Ia, int* D, int n, real* b);

void GaussD(real* Al, real* Di, int* Ia, int* D, int n, real* b);

void GaussLT(real* Al, real* Di, int* Ia, int* D, int n, real* b);

