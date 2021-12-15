#include "Chmetodi4.h";
#include <stdio.h>


int main()
{
   int n = 3;
   real* x = new real[n];
   real* b = new real[n];
   real** A = new real * [n];
   for (int i = 0; i < n; i++)
   {
      x[i] = i + 1;
      A[i] = new real[n];
   }
   A[0][0] = 2;
   A[0][1] = 2;
   A[0][2] = 4;
   A[1][0] = 1;
   A[1][1] = 3;
   A[1][2] = 8;
   A[2][0] = 2;
   A[2][1] = 5;
   A[2][2] = 15;
   MatrixMult(A, x, b, n);
   SolveSlae(A, b, n);
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
void Newton(int n, int m, real* x0)
{
   real** J = new real * [m];
   real* F = new real[m];
   for (int i = 0; i < m; i++)
   {
      J[i] = new real[m];
   }
   CalculateMinusF(F, x0, n, m);
   CalculateJakobi(J, x0, n, m);
   SolveSlae(J)

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