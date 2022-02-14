#include<stdio.h>
#include "umf1.h"
#include <vector>
#include <set>
//Область имеет Т-образную форму. Предусмотреть учет первых и вторых краевых условий. 
int main()
{
   int bc1count, bc2count;
   real lambda, gamma;
   real* xgrid = new real[4];
   real* ygrid = new real[3];
   int* xsplitcount = new int[3];
   int* ysplitcount = new int[2];
   int* xcoef = new int[3];
   int* ycoef = new int[2];
   FILE* file;
   fopen_s(&file, "grid.txt", "r");
   for (int i = 0; i < 4; i++)
   {
      fscanf_s(file, "%f", &(xgrid[i]));
   }
   for (int i = 0; i < 3; i++)
   {
      fscanf_s(file, "%f", &(ygrid[i]));
   }
   for (int i = 0; i < 3; i++)
   {
      fscanf_s(file, "%d", &(xsplitcount[i]));
   }
   for (int i = 0; i < 2; i++)
   {
      fscanf_s(file, "%d", &(ysplitcount[i]));
   }
   for (int i = 0; i < 3; i++)
   {
      fscanf_s(file, "%d", &(xcoef[i]));
   }
   for (int i = 0; i < 2; i++)
   {
      fscanf_s(file, "%d", &(ycoef[i]));
   }
   fscanf_s(file, "%d", &lambda);
   fscanf_s(file, "%d", &gamma);
   fclose(file);
   int bctype[7];
   real bcvalue[7];
   fopen_s(&file, "BC.txt", "r");
   for (int i = 0; i < 7; i++)
   {
      fscanf_s(file, "%d %f", &(bctype[i]), &(bcvalue[i]));
   }
   fclose(file);
   int n = (xsplitcount[1] + 1) * ysplitcount[0] + (ysplitcount[1] + 1) * (xsplitcount[0] + xsplitcount[1] + xsplitcount[2] + 1);
   real* hx = new real[3];
   real* hy = new real[2];
   for (int i = 0; i < 3; i++)
   {
      if (xcoef[i] != 1)
      {
         hx[i] = (xgrid[i + 1] - xgrid[i]) * (1 - xcoef[i]) / (1-quickpower(xcoef[i], xsplitcount[i]));
      }
      else
      {
         hx[i] = (xgrid[i + 1] - xgrid[i]) / xsplitcount[i];
      }
   }
   for (int i = 0; i < 2; i++)
   {
      if (ycoef[i] != 1)
      {
         hy[i] = (ygrid[i + 1] - ygrid[i]) * (1 - ycoef[i]) / (1-quickpower(ycoef[i], ysplitcount[i]));
      }
      else
      {
         hy[i] = (ygrid[i + 1] - ygrid[i]) / ysplitcount[i];
      }
   }
   int m = 2 * (n - 1) - xsplitcount[0] - xsplitcount[1] - xsplitcount[2];
   real* di = new real[n];
   real* b = new real[n];
   int* ia = new  int[n + 1];
   int* ja = new int[m];
   real* al = new real[m];
   real* au = new real[m];
   int k = 2;
   int l = xsplitcount[1] + 1;
   int ibeg = 1;
   int iend = (xsplitcount[1] + 1) * (ysplitcount[0] - 1);
   ja[0] = 1;
   ja[1] = l;
   ia[0] = 0;
   ia[1] = 0;
   if (bctype[0] == 1)
   {
      di[0] = 1;
      b[0] = bcvalue[0];
   }
   else
   {
      if (bctype[1] == 1)
      {
         di[0] = 1;
         b[0] = bcvalue[1];
      }
      else
      {
         di[0] = lambda;
         au[0] = -lambda;
         au[1] = 0;
         b[0] = bcvalue[1] * hx[1];
      }
   }
   for (int i = ibeg; i < iend; i++)
   {
      ja[k] = i + 1;
      k++;
      ja[k] = i + l;
      k++;
      ia[i + 1] = ia[i] + 2;
   }
   ibeg = iend;
   iend = ibeg + xsplitcount[1] + 1;
   l = xsplitcount[0] + xsplitcount[1] + 1;
   for (int i = ibeg; i < iend; i++)
   {
      ja[k] = i + 1;
      k++;
      ja[k] = i + l;
      k++;
      ia[i + 1] = ia[i] + 2;
   }
   ibeg = iend;
   iend = n - xsplitcount[0] - xsplitcount[1] - xsplitcount[2];
   l = +xsplitcount[0] + xsplitcount[1] + xsplitcount[2] + 1;
   for (int i = ibeg; i < iend; i++)
   {
      ja[k] = i + 1;
      k++;
      ja[k] = i + l;
      k++;
      ia[i + 1] = ia[i] + 2;
   }
   ibeg = iend;
   iend = n;
   for (int i = ibeg; i < iend; i++)
   {
      ja[k] = i + 1;
      k++;
      ia[i + 1] = ia[i] + 1;
   }

   printf_s("sosi trak");
}

real quickpower(real x, int n)
{
   real res = 1;
   real q = x;
   int k = n;
   while (k != 0)
   {
      if (k % 2 == 1)
         res *= q;
      k >>= 1;
      q *= x;
   }
   return res;
}