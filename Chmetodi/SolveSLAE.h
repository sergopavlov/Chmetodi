#pragma once
#define Float
#ifdef Float
typedef float real;
typedef float reals;
#define str "%10.7f %13.7e\n"
#define str2 "%f"
#endif // Float
#ifdef FloatDouble
typedef float real;
typedef double reals;
#define str "%10.7f %13.7e\n"
#define str2 "%f"
#endif // Float
#ifdef Double
typedef double real;
typedef double reals;
#define str "%20.15lf %20.15e\n"
#define str2 "%lf"
#endif // Float

void Solve(real* Al, real* Di, int* Ia, int* D, int n, real* b);

void LDLT(real* Al, real* Di, int* Ia, int* D, int n);

void GaussL(real* Al, real* Di, int* Ia, int* D, int n, real* b);

void GaussD(int* D, int n, real* b);

void GaussLT(real* Al, real* Di, int* Ia, int* D, int n, real* b);

void MatrixMult(real* Al, real* Di, int* Ia, int n, real* y, real* x);

void MatrixMultL(real* Al, real* Di, int* Ia, int n, real* y, real* x);

void MatrixMultU(real* Al, real* Di, int* Ia, int n, real* y, real* x);

void GenerateAk(real* Al, real* Di, int* Ia, int n, int k, real* b);

void GenegateGilbert(real* Al, real* Di, int* Ia, int n, real* b);
