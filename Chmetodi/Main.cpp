#include "SolveSLAE.h"
#include "InOut.h"
int main()
{
   int n, m;
   getdims(&n, &m);
   real* Al = new real[m];
   real* Di = new real[n];
   real* b = new real[n];
   int* Ia = new int[n + 1];//хранится индекс массива с которого начинается iтая строка
   int* D = new int[n];
   Al[0] = -2;
   Al[1] = -4;
   Al[2] = 7;
   Al[3] = 3;
   Al[4] = 17;

   Di[0] = -1;
   Di[1] = 5;
   Di[2] = 45;
   Di[3] = 14;

   Ia[0] = 0;
   Ia[1] = 0;
   Ia[2] = 1;
   Ia[3] = 3;
   Ia[4] = 5;

   b[0] = -1;
   b[1] = 1;
   b[2] = 1;
   b[3] = 1;
   LDLT(Al, Di, Ia, D, n);
}



