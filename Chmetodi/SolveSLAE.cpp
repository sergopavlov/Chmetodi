#include "SolveSLAE.h"
#include <iostream>
#include <stdlib.h>
#include "time.h"

void Solve(real* Al, real* Di, int* Ia, int* D, int n, real* b)
{
   LDLT(Al, Di, Ia, D, n);
   GaussL(Al, Di, Ia, D, n, b);
   GaussD(D, n, b);
   GaussLT(Al, Di, Ia, D, n, b);
}
void LDLT(real* Al, real* Di, int* Ia, int* D, int n)
{

   for (int i = 0; i < n; i++)
   {
      reals sumrow = 0;
      int j0 = i - (Ia[i + 1] - Ia[i]);//с какого j начинается профиль iтой строки
      //в следующем цикле проходится профиль iтой строки до диагонали
      int dind = j0;
      for (int ii = Ia[i]; ii < Ia[i + 1]; ii++, dind++)//iiтый элемент Al это iтый элемент профиля iтой строки
      {
         int j = j0 + ii - Ia[i];//j текущего элемента
         int j0j = j - (Ia[j + 1] - Ia[j]);//с какого j начинается профиль jтой строки

         int kbeg = j0 > j0j ? j0 : j0j;
         int kend = i > j ? j : i;//выбираим наименьший из профилей iтой и jтой строки
         reals cursum = 0;
         int indexi = Ia[i] + kbeg - j0;
         int indexj = Ia[j] + kbeg - j0j;
         for (int k = 0; k < kend - kbeg; k++, indexi++, indexj++)
         {
            cursum += (reals)(Al[indexi] * Al[indexj] * D[kbeg + k]);
         }
         Al[ii] -= (real)cursum;
         Al[ii] = Al[ii] / Di[j] / D[j];
         sumrow += (reals)(Al[ii] * Al[ii] * D[dind]);
      }
      Di[i] -= (real)sumrow;
      D[i] = Di[i] > 0 ? 1 : -1;
      Di[i] = sqrt(abs(Di[i]));
   }
}
void GaussL(real* Al, real* Di, int* Ia, int* D, int n, real* b)
{
   for (int i = 0; i < n; i++)
   {
      reals cursum = 0;
      int jbeg = i - (Ia[i + 1] - Ia[i]);
      for (int j = Ia[i]; j < Ia[i + 1]; j++, jbeg++)
      {
         cursum += (reals)(Al[j] * b[jbeg]);
      }
      b[i] = (b[i] - (real)cursum) / Di[i];
   }
}

void GaussD(int* D, int n, real* b)
{
   for (int i = 0; i < n; i++)
   {
      b[i] /= D[i];
   }
}
void GaussLT(real* Al, real* Di, int* Ia, int* D, int n, real* b)
{
   for (int i = n - 1; i >= 0; i--)
   {
      reals cursum = 0;
      for (int j = n - 1; j > i; j--)
      {
         if (Ia[j + 1] - Ia[j] >= j - i)
         {
            cursum += (reals)(Al[Ia[j + 1] - j + i] * b[j]);
         }
      }
      b[i] = (b[i] - (real)cursum) / Di[i];
    }
}

void MatrixMult(real* Al, real* Di, int* Ia, int n, real* y, real* x)
{
   for (int i = 0; i < n; i++)
   {
      y[i] = Di[i] * x[i];
      int i0 = Ia[i];
      int i1 = Ia[i + 1];
      int j = i - (i1 - i0);
      for (int k = i0; k < i1; k++, j++)
      {
         y[i] += Al[k] * x[j];
         y[j] += Al[k] * x[i];
      }
   }
}
void MatrixMultL(real* Al, real* Di, int* Ia, int n, real* y, real* x)
{
   for (int i = 0; i < n; i++)
   {
      y[i] = Di[i] * x[i];
      int i0 = Ia[i];
      int i1 = Ia[i + 1];
      int j = i - (i1 - i0);
      for (int k = i0; k < i1; k++, j++)
      {
         y[i] += Al[k] * x[j];
      }
   }
}
void MatrixMultU(real* Al, real* Di, int* Ia, int n, real* y, real* x)
{
   for (int i = 0; i < n; i++)
   {
      y[i] = Di[i] * x[i];
      int i0 = Ia[i];
      int i1 = Ia[i + 1];
      int j = i - (i1 - i0);
      for (int k = i0; k < i1; k++, j++)
      {
         y[j] += Al[k] * x[i];
      }
   }
}

void GenerateAk(real* Al, real* Di, int* Ia, int n, int k, real* b)
{
   srand(time(NULL));
   Ia[0] = 0;
   Ia[1] = 0;
   Ia[2] = 1;
   Di[0] = 0;
   real* x = new real[n];
   x[0] = 1;
   for (int i = 2; i < n; i++)
   {
      Ia[i + 1] = Ia[i] + 1 + rand() % (i - 1);
   }
   for (int i = 1; i < n; i++)
   {
      x[i] = 1;
      Di[i] = 0;
      Al[Ia[i]] = -1;
      for (int j = Ia[i] + 1; j < Ia[i + 1]; j++)
      {
         Al[j] = -(rand() % 5);
      }
   }
   MatrixMult(Al, Di, Ia, n, b, x);
   for (int i = 0; i < n; i++)
   {
      Di[i] = -b[i];
      x[i] = i + 1;
   }
}

void GenegateGilbert(real* Al, real* Di, int* Ia, int n, real* b)
{
   Ia[0] = 0;
   Ia[1] = 0;
   Di[0] = 1;
   for (int i = 1; i < n; i++)
   {
      Di[i] = 1.0 / (2 * i + 1);
      Ia[i + 1] = Ia[i] + i;
      int ind = Ia[i];
      for (int j = 0; j < i; j++, ind++)
      {
         Al[ind] = 1.0 / (i + j + 1);
      }
   }
}