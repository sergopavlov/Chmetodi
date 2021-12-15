#include "Chmetodi4.h";
#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;
vector<real(*)(real*, int)> funcs;

int main()
{
   int n = 2, m = 2;
   real* x0 = new real[m];

   funcs.push_back(&f1);
   funcs.push_back(&f2);
   for (int i = 0; i < m; i++)
   {
      x0[i] = 1;
   }
   x0[0] = 100;
   int k = Newton(n, m, x0, 1e-6, 1e-6, 10000);
   printf_s("asdasd");
}

void CalculateMinusF(real* f, real* x, int n, int m)
{
   f[0] = -((x[0] - 2) * (x[0] - 2) + x[1] * x[1] - 9);
   f[1] = -((x[0] + 2) * (x[0] + 2) + x[1] * x[1] - 9);
}


void CalculateJakobi(real** J, real* x, int n, int m)//m уравнений n  неизвестных n>m
{
   J[0][0] = 2 * (x[0] - 2);
   J[0][1] = 2 * x[1];
   J[1][0] = 2 * (x[0] + 2);
   J[1][1] = 2 * x[1];
}

real f1(real* x, int n)
{
   return (x[0] - 2) * (x[0] - 2) + x[1] * x[1] - 9;
}

real f2(real* x, int n)
{
   return (x[0] - 2) * (x[0] + 2) + x[1] * x[1] - 9;
}

int Newton(int n, int m, real* x0, real eps1, real eps2, int maxiter)
{
   real** J = new real * [m];
   real* F = new real[m];
   real* Fnext = new real[m];
   real* xnext = new real[m];
   real Fnormnext;
   real Fnorm;
   real b;
   bool flagnotend = true;
   for (int i = 0; i < m; i++)
   {
      J[i] = new real[m];
   }
   CalculateMinusF(F, x0, n, m);
   real F0 = CalcNorm(F, m);
   int k = 0;
   while (flagnotend && k < maxiter)
   {
      CalculateMinusF(F, x0, n, m);
      CalculateJakobi(J, x0, n, m);
      Fnorm = CalcNorm(F, m);
      SolveSlae(J, F, n);
      b = 1;
      bool flag = true;
      while (flagnotend && flag)
      {
         if (b < eps1)
            flagnotend = false;
         for (int i = 0; i < m; i++)
         {
            xnext[i] = x0[i] + b * F[i];
         }
         CalculateMinusF(Fnext, xnext, n, m);
         Fnormnext = CalcNorm(Fnext, m);
         if (Fnormnext < Fnorm)
         {
            flag = false;
         }
         b /= 2;
      }
      for (int i = 0; i < m; i++)
      {
         x0[i] = xnext[i];
      }
      if (Fnormnext / F0 < eps2)
         flagnotend = false;
      k++;
   }
   return k;
}
real CalcNorm(real* x, int n)
{
   real summ = 0;
   for (int i = 0; i < n; i++)
   {
      summ += x[i] * x[i];
   }
   return sqrt(summ);
}

void SolveSlae(real** A, real* b, int n)
{
   for (int i = 0; i < n; i++)
   {
      real summd = 0;
      for (int j = 0; j < i; j++)
      {
         real summl = 0;
         real summu = 0;
         for (int k = 0; k < j; k++)
         {
            summl += A[i][k] * A[k][j];
            summu += A[j][k] * A[k][i];
         }
         A[i][j] -= summl;
         A[j][i] = (A[j][i] - summu) / A[j][j];
         summd += A[i][j] * A[j][i];
      }
      A[i][i] -= summd;
   }
   for (int i = 0; i < n; i++)
   {
      real summ = 0;
      for (int j = 0; j < i; j++)
      {
         summ += A[i][j] * b[j];
      }
      b[i] = (b[i] - summ) / A[i][i];
   }
   for (int i = n - 1; i >= 0; i--)
   {
      real summ = 0;
      for (int j = n - 1; j > i; j--)
      {
         summ += A[i][j] * b[j];
      }
      b[i] -= summ;
   }
}
void MatrixMult(real** A, real* x, real* b, int n)
{
   for (int i = 0; i < n; i++)
   {
      b[i] = 0;
      for (int j = 0; j < n; j++)
      {
         b[i] += A[i][j] * x[j];
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