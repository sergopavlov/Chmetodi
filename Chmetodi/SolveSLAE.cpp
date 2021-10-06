#include "SolveSLAE.h"
#include <iostream>
void Solve(real* Al, real* Di, int* Ia, int* D, int n, real* b)
{
   LDLT(Al, Di, Ia, D, n);
   GaussL(Al, Di, Ia, D, n, b);
   GaussD(Al, Di, Ia, D, n, b);
   GaussLT(Al, Di, Ia, D, n, b);
}
void LDLT(real* Al, real* Di, int* Ia, int* D, int n)
{

   for (int i = 0; i < n; i++)
   {
      int j0 = i - (Ia[i + 1] - Ia[i]);//с какого j начинается профиль iтой строки
      //в следующем цикле проходится профиль iтой строки до диагонали
      for (int ii = Ia[i]; ii < Ia[i + 1]; ii++)//iiтый элемент Al это iтый элемент профиля iтой строки
      {

         int j = j0 + ii - Ia[i];//j текущего элемента
         int j0j = j - (Ia[j + 1] - Ia[j]);//с какого j начинается профиль jтой строки

         int kbeg = j0 > j0j ? j0 : j0j;
         int kend = i > j ? j : i;//выбираим наименьший из профилей iтой и jтой строки
         real cursum = 0;
         for (int k = 0; k < kend - kbeg; k++)
         {
            int indexi = Ia[i] + kbeg - j0 + k;
            int indexj = Ia[j] + kbeg - j0j + k;
            cursum += Al[indexi] * Al[indexj] * D[kbeg + k];
         }
         Al[ii] -= cursum;
         Al[ii] = Al[ii] / Di[j] / D[j];
      }
      //считаем диагональный элемент
      real sumrow = 0;
      for (int s = 0; s < Ia[i + 1] - Ia[i]; s++)
      {
         sumrow += Al[Ia[i] + s] * Al[Ia[i] + s] * D[i - Ia[i + 1] + Ia[i] + s];
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
      real cursum = 0;
      int jbeg = i - (Ia[i + 1] - Ia[i]);
      for (int j = 0; j < Ia[i + 1] - Ia[i]; j++)
      {
         cursum += Al[Ia[i] - 1 + j] * b[jbeg + j];
      }
      b[i] = (b[i] - cursum) / Di[i];
   }
}
void GaussD(real* Al, real* Di, int* Ia, int* D, int n, real* b)
{
   for (int i = 0; i < n; i++)
   {
      b[i] *= D[i];
   }
   // test
}
void GaussLT(real* Al, real* Di, int* Ia, int* D, int n, real* b)
{
   for (int i = n - 1; i >= 0; i--)
   {
      real cursum = 0;
      for (int j = n - 1; j > i; j--)
      {
         if (Ia[j + 1] - Ia[j] >= j - i)
         {
            cursum += Al[Ia[j + 1] - j + i - 1] * b[j];
         }
      }
      b[i] = (b[i] - cursum) / Di[i];
   }
}