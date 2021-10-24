#include <stdio.h>
#include "Source.h"
#include "InputOutput.h"

void Inputparameters(int* n, int* m, real* presision, int* maxiter)
{
   FILE* file;
   fopen_s(&file, "Parameters.txt", "r");
   fscanf_s(file, "%d %d %f %d", n, m, presision, maxiter);
   fclose(file);
}

void Input(int n,int m, real** mat, real* b, real* x0)
{
   FILE* file;
   fopen_s(&file, "Matrix.txt", "r");
   for (int i = 0; i < n - 3 - m; i++)
   {
      fscanf_s(file, "%f", &(mat[0][i]));
   }
   for (int i = 0; i < n - 2 - m; i++)
   {
      fscanf_s(file, "%f", &(mat[1][i]));
   }
   for (int i = 0; i < n - 1; i++)
   {
      fscanf_s(file, "%f", &mat[2][i]);
   }
   for (int i = 0; i < n; i++)
   {
      fscanf_s(file, "%f", &mat[3][i]);
   }
   for (int i = 1; i < n; i++)
   {
      fscanf_s(file, "%f", &mat[4][i]);
   }
   for (int i = 2 + m; i < n; i++)
   {
      fscanf_s(file, "%f", &mat[5][i]);
   }
   for (int i = 3 + m; i < n; i++)
   {
      fscanf_s(file, "%f", &mat[6][i]);
   }
   fclose(file);

   fopen_s(&file, "b.txt", "r");
   for (int i = 0; i < n; i++)
   {
      fscanf_s(file, "%f", &b[i]);
   }
   fclose(file);

   fopen_s(&file, "x0.txt", "r");
   for (int i = 0; i < n; i++)
   {
      fscanf_s(file, "%f", &x0[i]);
   }
   fclose(file);
}
