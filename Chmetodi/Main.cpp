#include "SolveSLAE.h"
#include "InOut.h"
#include "stdio.h"
#include "Math.h"




int main()
{
   int n = 10;
   int m = 19;
   real* Al = new real[m];
   real* Di = new real[n];
   real* b = new real[n];
   int* Ia = new int[n + 1];
   int* D = new int[n];
   real* xtrue = new real[n];
   real* z = new real[n];
   real* y = new real[n];

   int k = 0;
   for (int i = 0; i < n; i++)
   {
      xtrue[i] = i + 1;
   }
   k = 5;
   {
      printf_s("k = %d \n", k);
      int s = 1;
      for (int i = 0; i < k; i++)
      {
         s *= 10;
      }
      input(Al, Di, b, Ia, n, m);
      Di[0] += 1.0 / s;
      MatrixMult(Al, Di, Ia, n, b, xtrue);
      //Solve(Al, Di, Ia, D, n, b);
      LDLT(Al, Di, Ia, D, n);
      MatrixMultU(Al, Di, Ia, n, y, xtrue);
      MatrixMultL(Al, Di, Ia, n, z, y);

      GaussL(Al, Di, Ia, D, n, b);
      for (int i = 0; i < n; i++)
      {
         printf_s(str, b[i], fabs(y[i] - b[i]));
      }
      printf_s("\n\n\n\n");
      GaussLT(Al, Di, Ia, D, n, b);
      for (int i = 0; i < n; i++)
      {
         printf_s(str, b[i], fabs(xtrue[i] - b[i]));
      }

   }

}

/*  GenerateAk(Al, Di, Ia, n, k, b);


  FILE* in;
  fopen_s(&in, "Al.txt", "w");
  for (int i = 0; i < Ia[n]; i++)
  {
     fprintf_s(in, "%f ", Al[i]);
  }
  fclose(in);

  fopen_s(&in, "Di.txt", "w");
  for (int i = 0; i < n; i++)
  {
     fprintf_s(in, "%f ", Di[i]);
  }
  fclose(in);

  fclose(in);

  fopen_s(&in, "b.txt", "w");
  for (int i = 0; i < n; i++)
  {
     fprintf_s(in, "%f ", b[i]);
  }
  fclose(in);

  fopen_s(&in, "Ia.txt", "w");
  for (int i = 0; i <= n; i++)
  {
     fprintf_s(in, "%d ", Ia[i]);
  }
  fclose(in);*/


