#include <stdio.h>
#include <cmath>
#include "Source.h"
#include "InputOutput.h"

int main()
{
   real** mat;
   real* b;
   real* x0;
   real* xtrue;
   real precision;
   int maxiter, n, m;
   Inputparameters(&n, &m, &precision, &maxiter);
   mat = new real * [7];
   b = new real[n];
   x0 = new real[n];
   xtrue = new real[n];
   for (int i = 0; i < n; i++)
   {
      xtrue[i] = i + 1;
   }
   for (int i = 0; i < 7; i++)
   {
      mat[i] = new real[n];
   }
   Input(n, m, mat, b, x0);
   real* x = new real[n];
   real omega = 1.1;
   SolveZeidelRelax(n, m, precision, maxiter, mat, b, x0, omega);
   for (int i = 0; i < n; i++)
   {
      printf_s("%f\n", x0[i]);
   }
}

void JacobiIterationRelax(int n, int m, real** mat, real* b, real* x0, real* x, real omega)
{
   for (int i = 0; i < n; i++)
   {
      reals cursumm = 0;
      if (i < n - 3 - m)
      {
         cursumm += mat[0][i] * x0[3 + m + i];
      }
      if (i < n - 2 - m)
      {
         cursumm += mat[1][i] * x0[m + 2 + i];
      }
      if (i < n - 1)
      {
         cursumm += mat[2][i] * x0[i + 1];
      }
      cursumm += mat[3][i] * x0[i];
      if (i >= 1)
      {
         cursumm += mat[4][i] * x0[i - 1];
      }
      if (i >= 2 + m)
      {
         cursumm += mat[5][i] * x0[i - m - 2];
      }
      if (i >= 3 + m)
      {
         cursumm += mat[6][i] * x0[i - 3 - m];
      }
      x[i] = x0[i] + omega * (b[i] - cursumm) / mat[3][i];
   }
}

void BlockRelaxIteration(int n, int m, int p, real** mat, real* b, real* x0, real* x, real omega)
{
   if (n % p == 0)
   {

   }
}

void MatrixMult(int n, int m, real** mat, real* x, real* b)//Ax=b
{
   for (int i = 0; i < n; i++)
   {
      b[i] = mat[3][i] * x[i];
   }
   for (int i = 0; i < n - m - 3; i++)
   {
      b[i] += mat[0][i] * x[i + m + 3];
   }
   for (int i = 0; i < n - 2 - m; i++)
   {
      b[i] += mat[1][i] * x[i + m + 2];
   }
   for (int i = 0; i < n - 1; i++)
   {
      b[i] += mat[2][i] * x[i + 1];
   }
   for (int i = 1; i < n; i++)
   {
      b[i] += mat[4][i] * x[i - 1];
   }
   for (int i = 2 + m; i < n; i++)
   {
      b[i] += mat[5][i] * x[i - 2 - m];
   }
   for (int i = 3 + m; i < n; i++)
   {
      b[i] += mat[6][i] * x[i - 3 - m];
   }
}

int SolveJacobiRelax(int n, int m, real precision, int maxiter, real** mat, real* b, real* x0, real* x, real omega)
{
   int k = 0;
   real relativeresidual = 1;
   real* curb;
   curb = new real[n];
   while (k < maxiter && relativeresidual > precision)
   {
      JacobiIterationRelax(n, m, mat, b, x0, x, omega);
      MatrixMult(n, m, mat, x, curb);
      real summ1 = 0, summ2 = 0;
      for (int i = 0; i < n; i++)
      {
         summ1 += (b[i] - curb[i]) * (b[i] - curb[i]);
         summ2 += b[i] * b[i];
         x0[i] = x[i];
      }
      relativeresidual = sqrt(summ1 / summ2);
      k++;
   }
   return k;
}

int  SolveZeidelRelax(int n, int m, real precision, int maxiter, real** mat, real* b, real* x0, real omega)
{  
   int k = 0;
   real relativeresidual = 1;
   real* curb;
   curb = new real[n];
   while (k < maxiter && relativeresidual > precision)
   {
      JacobiIterationRelax(n, m, mat, b, x0, x0, omega);
      MatrixMult(n, m, mat, x0, curb);
      real summ1 = 0, summ2 = 0;
      for (int i = 0; i < n; i++)
      {
         summ1 += (b[i] - curb[i]) * (b[i] - curb[i]);
         summ2 += b[i] * b[i];
      }
      relativeresidual = sqrt(summ1 / summ2);
      k++;
   }
   return k;
}