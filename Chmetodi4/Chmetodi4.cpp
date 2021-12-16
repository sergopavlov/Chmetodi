#include "Chmetodi4.h";
#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;
vector<real(*)(real*, int)> funcs;
vector<vector<real(*)(real*, int)>> funcdiffs;
vector<int> nums1;
vector<int> nums2;
vector<real> vals;

int main()
{
   int n = 2, m = 2;
   real* x0 = new real[n];
   funcdiffs.resize(m);
   nums1.resize(m);
   vals.resize(m);
   nums2.resize(n);
   funcs.push_back(&f1);
   funcs.push_back(&f2);
   //funcs.push_back(&f3);
   funcdiffs[0].push_back(&f11);
   funcdiffs[0].push_back(&f12);
   funcdiffs[1].push_back(&f21);
   funcdiffs[1].push_back(&f22);
   //funcdiffs[2].push_back(&f31);
   //funcdiffs[2].push_back(&f32);
   x0[0] = 2;
   x0[1] = 1;

   int k = Newton2(n, m, x0, 1e-6, 1e-6, 10000);
   printf_s("asdasd");
}

void CalculateMinusF2(real* f, real* x, int n, int m)
{
   f[0] = -funcs[0](x, n);
   nums2[0] = 0;
   for (int i = 1; i < m; i++)
   {
      real cur = -funcs[i](x, n);
      int jend = min(i, n);
      bool flag = true;
      for (int j = 0; j < jend && flag; j++)
      {
         if (abs(cur) >= abs(f[j]))
         {
            flag = false;
            int kbeg = min(i - 1, n - 2);
               for (int k = kbeg; k >= j; k--)
               {
                  f[k + 1] = f[k];
                  nums2[k + 1] = nums2[k];
               }
            f[j] = cur;
            nums2[j] = i;
         }
      }
      if (flag&&i<n)
      {
         f[i] = cur;
         nums2[i] = i;
      }
   }
}

real CalculateNormF(real* x, int m)
{
   real summ = 0;
   for (int i = 0; i < m; i++)
   {
      summ += funcs[i](x, m) * funcs[i](x, m);
   }
   return sqrt(summ);
}

void CalculateJakobi2(real** J, real* x, int n, int m)
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         J[i][j] = funcdiffs[nums2[i]][j](x, n);
      }
   }
}

int Newton1(int n, int m, real* x0, real eps1, real eps2, int maxiter)//n>m
{
   real** J = new real * [m];
   real* F = new real[m];
   real* Fnext = new real[m];
   real* xnext = new real[n];
   real Fnormnext;
   real Fnorm;
   real b;
   bool flagnotend = true;
   for (int i = 0; i < m; i++)
   {
      J[i] = new real[m];
   }
   real F0 = CalculateNormF(x0, m);
   int k = 0;
   while (flagnotend && k < maxiter)
   {
      CalculateJacobi1(J, x0, n, m);
      CalculateMinusF1(F, x0, n, m);
      Fnorm = CalculateNormF(x0, m);
      SolveSlae(J, F, m);
      b = 1;
      bool flag = true;
      while (flagnotend && flag)
      {
         for (int i = 0; i < n; i++)
         {
            xnext[i] = x0[i];
         }
         for (int i = 0; i < m; i++)
         {
            xnext[nums1[i]] += b * F[i];
         }
         Fnormnext = CalculateNormF(xnext, m);
         if (Fnormnext < Fnorm)
         {
            flag = false;
         }
         b /= 2;
         if (b < eps1)
            flagnotend = false;
      }
      for (int i = 0; i < n; i++)
      {
         x0[i] = xnext[i];
      }
      if (Fnormnext / F0 < eps2)
         flagnotend = false;
      k++;
   }
   return k;
}

void CalculateJacobi1(real** J, real* x, int n, int m)
{
   for (int i = 0; i < m; i++)
   {
      J[i][0] = funcdiffs[i][0](x, n);
      if (abs(J[i][0]) > vals[0])
         vals[0] = abs(J[0][i]);
   }
   nums1[0] = 0;
   for (int i = 1; i < n; i++)
   {
      real curval = 0;
      real* cur = new real[m];
      for (int j = 0; j < m; j++)
      {
         cur[j] = funcdiffs[j][i](x, n);
         if (abs(cur[i]) > curval)
            curval = abs(cur[i]);
      }
      int jend = min(i, n);
      bool flag = true;
      for (int j = 0; j < i; j++)
      {
         if (curval >= vals[j])
         {
            flag = false;
            int kbeg = min(i - 1, m - 2);
            if (j != i - 1)
            {
               for (int k = kbeg; k >= j; k--)
               {
                  for (int p = 0; p < m; p++)
                  {
                     J[k + 1][p] = J[k][p];
                  }
                  nums1[k + 1] = nums1[k];
               }
            }
            for (int p = 0; p < m; p++)
            {
               J[j][p] = cur[p];
               nums1[j] = i;
            }
         }
      }
   }
}

void CalculateMinusF1(real* f, real* x, int n, int m)
{
   for (int i = 0; i < m; i++)
   {
      f[i] = -funcs[i](x, n);
   }
}

int Newton2(int n, int m, real* x0, real eps1, real eps2, int maxiter)//m уравнений n  неизвестных n<m
{
   real** J = new real * [n];
   real* F = new real[n];
   real* Fnext = new real[n];
   real* xnext = new real[n];
   real Fnormnext;
   real Fnorm;
   real b;
   bool flagnotend = true;
   for (int i = 0; i < n; i++)
   {
      J[i] = new real[n];
   }
   real F0 = CalculateNormF(x0, m);
   int k = 0;
   while (flagnotend && k < maxiter)
   {
      CalculateMinusF2(F, x0, n, m);
      CalculateJakobi2(J, x0, n, m);
      Fnorm = CalculateNormF(x0, m);
      SolveSlae(J, F, n);
      b = 1;
      bool flag = true;
      while (flagnotend && flag)
      {
         if (b < eps1)
            flagnotend = false;
         for (int i = 0; i < n; i++)
         {
            xnext[i] = x0[i] + b * F[i];
         }
         Fnormnext = CalculateNormF(xnext, m);
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

real f1(real* x, int n)
{
   return (x[0] - 4) * (x[0] - 4) + x[1] * x[1] - 25;
}

real f2(real* x, int n)
{
   return (x[0] + 4) * (x[0] + 4) + x[1] * x[1] - 25;
}

real f3(real* x, int n)
{
   return x[0];
}

real f11(real* x, int n)
{
   return 2 * (x[0] - 4);
}

real f12(real* x, int n)
{
   return 2 * x[1];
}

real f21(real* x, int n)
{
   return 2 * (x[0] + 4);
}

real f22(real* x, int n)
{
   return 2 * x[1];
}

real f31(real* x, int n)
{
   return 1;
}

real f32(real* x, int n)
{
   return 0;
}