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
      int j0 = i - (Ia[i + 1] - Ia[i]);//ñ êàêîãî j íà÷èíàåòñÿ ïðîôèëü iòîé ñòðîêè
      //â ñëåäóþùåì öèêëå ïðîõîäèòñÿ ïðîôèëü iòîé ñòðîêè äî äèàãîíàëè
      int dind = j0;
      for (int ii = Ia[i]; ii < Ia[i + 1]; ii++, dind++)//iiòûé ýëåìåíò Al ýòî iòûé ýëåìåíò ïðîôèëÿ iòîé ñòðîêè
      {
         int j = j0 + ii - Ia[i];//j òåêóùåãî ýëåìåíòà
         int j0j = j - (Ia[j + 1] - Ia[j]);//ñ êàêîãî j íà÷èíàåòñÿ ïðîôèëü jòîé ñòðîêè

         int kbeg = j0 > j0j ? j0 : j0j;
         int kend = i > j ? j : i;//âûáèðàèì íàèìåíüøèé èç ïðîôèëåé iòîé è jòîé ñòðîêè
         real cursum = 0;
         int indexi = Ia[i] + kbeg - j0;
         int indexj = Ia[j] + kbeg - j0j;
         for (int k = 0; k < kend - kbeg; k++, indexi++, indexj++)
         {
            cursum += Al[indexi] * Al[indexj] * D[kbeg + k];
         }
         Al[ii] -= cursum;
         Al[ii] = Al[ii] / Di[j] / D[j];
         sumrow += Al[ii] * Al[ii] * D[dind];
      }
      Di[i] -= sumrow;
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
         cursum += Al[j] * b[jbeg];
      }
      b[i] = (b[i] - cursum) / Di[i];
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
            cursum += Al[Ia[j + 1] - j + i] * b[j];
         }
      }
      b[i] = (b[i] - cursum) / Di[i];
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

void Gauss(real** A, int n, real* x, real* b)
{
   for (int k = 0; k < n; k++)
   {
      for (int i = k + 1; i < n; i++)
      {
         real buf = A[i][k];
         for (int j = k; j < n; j++)
         {
            A[i][j] -= A[k][j] * buf / A[k][k];
         }
         b[i] -= b[k] * buf / A[k][k];
      }
   }
   for (int i = n - 1; i >= 0; i--)
   {
      reals cursum = 0;
      for (int j = n - 1; j > i; j--)
      {
         cursum += A[i][j] * x[j];
      }
      x[i] = (b[i] - cursum) / A[i][i];
   }
}

void Multmatr(real** A, real* x, real* b, int n)
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

void Calc(real* Al, real* Di, int* Ia, int n, real* y, real* b)//Ly=b
{
   for (int i = 0; i < n; i++)
   {
      real cursum = 0;;

      int i0 = Ia[i];
      int i1 = Ia[i + 1];
      int j = i - (i1 - i0);
      for (int k = i0; k < i1; k++, j++)
      {
         cursum += Al[k] * y[j];
      }
      y[i] = (b[i] - cursum) / Di[i];
   }
}

void GenegateGilbert(real* Al, real* Di, int* Ia, int n)
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