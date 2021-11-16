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
   real lambdamax = GetMaxEugenValue(n, ia, di, au, al);
  real lambdamin = GetMinEugenvalue(n, ia, di, au, al);

   printf_s("%f %f", lambdamax, lambdamin);
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

void LUfactorization(int n, int* ia, real* di, real* au, real* al)
{
   for (int i = 0; i < n; i++)
   {
      real sumrow = 0;
      int j0 = i - (ia[i + 1] - ia[i]);
      int dind = j0;
      for (int ii = ia[i]; ii < ia[i + 1]; ii++, dind++)
      {
         int j = j0 + ii - ia[i];
         int j0j = j - (ia[j + 1] - ia[j]);

         int kbeg = j0 > j0j ? j0 : j0j;
         int kend = i > j ? j : i;
         real summu = 0;
         real summl = 0;
         int indexi = ia[i] + kbeg - j0;
         int indexj = ia[j] + kbeg - j0j;
         for (int k = 0; k < kend - kbeg; k++, indexi++, indexj++)
         {
            summu += al[indexj] * au[indexi];
            summl += al[indexi] * au[indexj];
         }
         al[ii] -= summl;
         au[ii] = (au[ii] - summu) / di[j];
         sumrow += au[ii] * al[ii];
      }
      di[i] -= sumrow;
   }
}

void GaussU(real* au, real* di, int* ia, int n,real* b)
{
   for (int i = n - 1; i >= 0; i--)
   {
      real cursum = 0;
      for (int j = n - 1; j > i; j--)
      {
         if (ia[j + 1] - ia[j] >= j - i)
         {
            cursum += au[ia[j + 1] - j + i] * b[j];
         }
      }
      b[i] -=cursum;
   }
}
void GaussL(real* al, real* di, int* ia, int n, real* b)
{
   for (int i = 0; i < n; i++)
   {
      real cursum = 0;
      int jbeg = i - (ia[i + 1] - ia[i]);
      for (int j = ia[i]; j < ia[i + 1]; j++, jbeg++)
      {
         cursum += al[j] * b[jbeg];
      }
      b[i] = (b[i] - cursum) / di[i];
   }
}

real GetMinEugenvalue(int n, int* ia, real* di, real* au, real* al)
{
   LUfactorization(n, ia, di, au, al);
   real eps = 0.0001;
   int maxiter = 10000;
   real* x = new real[n];
   real* x1 = new real[n];
   x[0] = 1;
   real lambda;
   for (int i = 0; i < n; i++)
   {
      x[i] = 1;
   }
   real maxdeltalambda = 1;
   int k = 0;
   while (maxdeltalambda > eps && k < maxiter)
   {
      for (int i = 0; i < n; i++)
      {
         x1[i] = x[i];
      }
      GaussL(al, di, ia, n, x1);
      GaussU(au, di, ia, n, x1);
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
   delete(x);
   delete(x1);
   return 1/lambda;
}

real GetMaxEugenValue(int n, int* ia, real* di, real* au, real* al)
{
   real eps = 0.00001;
   int maxiter = 10000;
   real* x = new real[n];
   real* x1 = new real[n];
   real lambda;
   for (int i = 0; i < n; i++)
   {
      x[i] = 1;
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
   delete(x);
   delete(x1);
   return lambda;
}
