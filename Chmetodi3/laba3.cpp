#include <stdio.h>
#include "laba3.h"
#include <cmath>

int main()
{
   int n, m, maxiter;
   real eps;
   inputparams(&n, &m, &maxiter, &eps);
   int* ia = new int[n + 1];
   int* ja = new int[m];
   real* di = new real[n];
   real* al = new real[m];
   real* x = new real[n];
   real* x0 = new real[n];
   real* b = new real[n];
   real* xtrue = new real[n];
   for (int i = 0; i < n; i++)
   {
      xtrue[i] = i + 1;
   }
   input(ia, ja, di, al, x0, b, n, m);
   int k = MSG(ia, ja, n, al, di, x0, b, maxiter, eps);
   printf_s("asdasd");

}

void inputparams(int* n, int* m, int* maxiter, real* eps)
{
   FILE* file;
   fopen_s(&file, "params.txt", "r");
   fscanf_s(file, "%d %d %d %f", n, m, maxiter, eps);
   fclose(file);
}

void input(int* ia, int* ja, real* di, real* al, real* x0, real* b, int n, int m)
{
   FILE* file;
   fopen_s(&file, "ia.txt", "r");
   for (int i = 0; i < n + 1; i++)
   {
      fscanf_s(file, "%d", &ia[i]);
   }
   fclose(file);

   fopen_s(&file, "ja.txt", "r");
   for (int i = 0; i < m; i++)
   {
      fscanf_s(file, "%d", &ja[i]);
   }
   fclose(file);

   fopen_s(&file, "al.txt", "r");
   for (int i = 0; i < m; i++)
   {
      fscanf_s(file, "%f", &al[i]);
   }
   fclose(file);

   fopen_s(&file, "di.txt", "r");
   for (int i = 0; i < n; i++)
   {
      fscanf_s(file, "%f", &di[i]);
   }
   fclose(file);

   fopen_s(&file, "x0.txt", "r");
   for (int i = 0; i < n; i++)
   {
      fscanf_s(file, "%f", &x0[i]);
   }
   fclose(file);

   fopen_s(&file, "b.txt", "r");
   for (int i = 0; i < n; i++)
   {
      fscanf_s(file, "%f", &b[i]);
   }
   fclose(file);
}

int MSG(int* ia, int* ja, int n, real* al, real* di, real* x, real* b, int maxiter, real eps)
{
   real bnorm = sqrt(DotProduct(b, b, n));
   real* r = new real[n];
   real* z = new real[n];
   real* Az = new real[n];
   MatrixMult(ia, ja, n, al, di, x, r);
   for (int i = 0; i < n; i++)
   {
      r[i] = b[i] - r[i];
      z[i] = r[i];
   }
   real* p = new real[n];
   MatrixMult(ia, ja, n, al, di, z, p);
   int k = 0;
   real alpha, betta, rnorm = sqrt(DotProduct(r, r, n));
   while (k<maxiter && rnorm / bnorm>eps)
   {
      MatrixMult(ia, ja, n, al, di, z, Az);
      alpha = rnorm * rnorm / DotProduct(Az, z, n);
      for (int i = 0; i < n; i++)
      {
         x[i] += alpha * z[i];
         r[i] -= alpha * Az[i];
      }
      betta = 1 / rnorm * rnorm;
      rnorm = sqrt(DotProduct(r, r, n));
      betta *= rnorm * rnorm;
      for (int i = 0; i < n; i++)
      {
         z[i] = r[i] + betta * z[i];
      }
      k++;
   }
   printf_s("relative residual is: %f\n", rnorm * bnorm);
   return k;
}

real DotProduct(real* x, real* y, int n)
{
   real res = 0;
   for (int i = 0; i < n; i++)
   {
      res += x[i] * y[i];
   }
   return res;
}

void MatrixMult(int* ia, int* ja, int n, real* al, real* di, real* x, real* b)
{
   for (int i = 0; i < n; i++)
   {
      b[i] = x[i] * di[i];
      for (int k = ia[i]; k < ia[i + 1]; k++)
      {
         int j = ja[k];
         b[i] += al[k] * x[j];
         b[j] += al[k] * x[i];
      }
   }
}