#include "SolveSLAE.h"
#include "InOut.h"
#include "stdio.h"
#include <math.h>
#include <stdlib.h>
#include<time.h>
int main()
{

   /*int n = 4, m = 5;
   real* Al = new real[m];
   real* Di = new real[n];
   real* b = new real[n];
   int* Ia = new int[n + 1];
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

   b[0] = -7;
   b[1] = 13;
   b[2] = 65;
   b[3] = 34;

   LDLT(Al, Di, Ia, D, n);
   GaussL(Al, Di, Ia, D, n, b);
   GaussD(D, n, b);
   GaussLT(Al, Di, Ia, D, n, b);

   for (int i = 0; i < n; i++)
   {
      printf_s(str2,b[i]);
   }*/
   int n = 10;
   for (int k = 0; k < 15; k++)
   {

   real** Mat;
   real* b = new real[n];
   real* xtrue = new real[n];
   real* x = new real[n];
   real* odin = new real[n];
   for (int i = 0; i < n; i++)
   {
      odin[i] = 1;
   }
   for (int i = 0; i < n; i++)
   {
      xtrue[i] = i + 1;
   }
   Mat = new real * [n];
   for (int i = 0; i < n; i++)
   {
      Mat[i] = new real[n];
   }

   /*for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         Mat[i][j] = 1.0 / (i + j + 1);
      }
   }*/
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         if (i != j)
            Mat[i][j] = 1 + (i + j) % 4;
         else
            Mat[i][j] = 0;
      }
   }
   Multmatr(Mat, odin, b, n);
   for (int i = 0; i < n; i++)
   {
      Mat[i][i] = -b[i];
   }
   int s = 1;
   for (int i = 0; i < k; i++)
   {
      s *= 10;
   }
   Mat[0][0] += 1.0 / s;

   Multmatr(Mat, xtrue, b, n);
   /*Mat[0][0] = 1;
   Mat[0][1] = 15;
   Mat[0][2] = 27;
   Mat[0][3] = 45;
   Mat[0][4] = 46;
   Mat[1][0] = 2;
   Mat[1][1] = 3;
   Mat[1][2] = 37;
   Mat[1][3] = 42;
   Mat[1][4] = 22;
   Mat[2][0] = 22;
   Mat[2][1] = 34;
   Mat[2][2] = 32;
   Mat[2][3] = 52;
   Mat[2][4] = 43;
   Mat[3][0] = 42;
   Mat[3][1] = 31;
   Mat[3][2] = 49;
   Mat[3][3] = 10;
   Mat[3][4] = 7;
   Mat[4][0] = 44;
   Mat[4][1] = 47;
   Mat[4][2] = 9;
   Mat[4][3] = 8;
   Mat[4][4] = 15;*/
   Gauss(Mat, n, x, b);
   for (int i = 0; i < n; i++)
   {
      printf_s("%20.15lf %20.15lf\n", x[i], fabs(x[i] - xtrue[i]));
   }
   printf_s("%d------------\n",k+1);

   }

   /*srand(time(NULL));

   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         Mat[i][j] = rand() % 4 + 1;
      }
   }
   for (int i = 0; i < n; i++)
   {
      Mat[i][i] = 0;
   }
   real* x = new real[n];
   Multmatr(Mat, b, x, n);
   for (int i = 0; i < n; i++)
   {
      Mat[i][i] = -x[i];
   }
   int k = 0;
   int s = 1;
   for (int i = 0; i < k; i++)
   {
      s *= 10;
   }
   Mat[0][0] += 1.0 / s;
   real* xtrue = new real[n];
   for (int i = 0; i < n; i++)
   {
      xtrue[i] = i + 1;
   }
   real* b = new real[n];
   Multmatr(Mat, xtrue, b, n);
   Gauss(Mat, n, x, b);
   for (int i = 0; i < n; i++)
   {
      printf_s("%f %f\n", x[i], fabs(x[i] - xtrue[i]));
   }*/
   /*Al[0] = 3.75;
   Al[1] = -1.82;
   Al[2] = 1.68;
   Al[3] = 3;
   Al[4] = 17;

   Di[0] = 2.25;
   Di[1] = 4.29;
   Di[2] = 0.27;
   Di[3] = -1.45;

   Ia[0] = 0;
   Ia[1] = 0;
   Ia[2] = 1;
   Ia[3] = 2;
   Ia[4] = 3;

   b[0] = 6;
   b[1] = 6.22;
   b[2] = 0.13;
   b[3] = 0.23;*/
}