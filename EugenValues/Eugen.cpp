#include "Eugen.h"
#include <stdio.h>
#include <cmath>


int main()
{
   int n;
   int m;
   FILE* file;
   fopen_s(&file, "dims.txt", "r");
   fscanf_s(file, "%d %d", &n, &m);
   int* ia = new int[n + 1];
   real* al = new real[m];
   real* au = new real[m];
   real* di = new real[n];
   input(al, au, di, ia, n, m);
   real lambda = GetMaxEugenValue(n, ia, di, au, al);
   printf_s("%f", lambda);
}

void input(real* al, real* au, real* di, int* ia, int n, int m)
{
   FILE* file;
   fopen_s(&file, "al.txt", "r");
   for (int i = 0; i < m; i++)
   {
      fscanf_s(file, "%f", &al[i]);
   }
   fclose(file);

   fopen_s(&file, "au.txt", "r");
   for (int i = 0; i < m; i++)
   {
      fscanf_s(file, "%f", &au[i]);
   }
   fclose(file);

   fopen_s(&file, "di.txt", "r");
   for (int i = 0; i < n; i++)
   {
      fscanf_s(file, "%f", &di[i]);
   }
   fclose(file);

   fopen_s(&file, "ia.txt", "r");
   for (int i = 0; i < n + 1; i++)
   {
      fscanf_s(file, "%d", &ia[i]);
   }
   fclose(file);
}

void MatrixMult(int n, int* ia, real* di, real* au, real* al, real* x, real* b)
{
   for (int i = 0; i < n; i++)
   {
      b[i] = x[i] * di[i];
      int j = i - (ia[i + 1] - ia[i]);
      int k0 = ia[i];
      int k1 = ia[i + 1];
      for (int k = k0; k < k1; k++, j++)
      {
         b[i] += al[k] * x[j];
         b[j] += au[k] * x[i];
      }
   }
}

real GetMaxEugenValue(int n, int* ia, real* di, real* au, real* al)
{
   real eps = 0.0001;
   int maxiter = 10000;
   real* x = new real[n];
   real* x1 = new real[n];
   x[0] = 1;
   real lambda;
   for (int i = 1; i < n; i++)
   {
      x[i] = 0;
   }
   real maxdeltalambda = 1;
   int k = 0;
   while (maxdeltalambda > eps && k < maxiter)
   {
      MatrixMult(n, ia, di, au, al, x, x1);
      lambda = 0;
      real summ = 0;
      for (int i = 0; i < n; i++)
      {
         lambda += x1[i] / x[i];
         summ += x1[i] * x1[i];
      }
      summ = sqrt(summ);
      lambda /= n;
      maxdeltalambda = fabs(x1[0] / x[0] - lambda);
      for (int i = 0; i < n; i++)
      {
         if (fabs(x1[i] / x[i] - lambda) > maxdeltalambda)
            maxdeltalambda = fabs(x1[i] / x[i] - lambda);
         x[i] = x1[i] / summ;
      }
      k++;
   }
   printf_s("%d\n", k);
   return lambda;
}