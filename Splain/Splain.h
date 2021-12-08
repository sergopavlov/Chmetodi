typedef float real;
real getsollutionISplain(real x, int n, real* grid, real* q);

void getfuncarray(int n, real* f, real* grid);

real func(real x);

real getsollutionISplain(real x, int n, real* grid, real* q);
void ISplain(real* grid, real* f, real* q, int n);

void SSplain(real* grid, real* q, int n, real* x, real* y, int pcount,real alpha,real betta);

real psi1(real t);

real psi2(real t);

real psi3(real t);

real psi4(real t);
void MatrixMult(int* ia, int* ja, int n, real* al, real* di, real* x, real* b);
real DotProduct(real* x, real* y, int n);
int MSG(int* ia, int* ja, int n, real* al, real* di, real* x, real* b, int maxiter, real eps);