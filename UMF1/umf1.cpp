#include<stdio.h>
#include "umf1.h"
#include <math.h>
//ќбласть имеет “-образную форму. ѕредусмотреть учет первых и третьих краевых условий. 
real func(real x, real y)
{
   return -2 + x * x;
}
//u=x^4
//f= -12x^2+x^4
real BC(real x, real y, int edge)//краевые услови€
{
   real res = 0;
   switch (edge)
   {
   case 0:
      res = x * x;
      break;
   case 1:
      res = x * x;
      break;
   case 2:
      res = x * x;
      break;
   case 3:
      res = x * x;
      break;
   case 4:
      res = x * x;
      break;
   case 5:
      res = x * x;
      break;
   case 6:
      res = x * x;
      break;
   case 7:
      res = x * x;
      break;
   default:
      break;
   }
   return res;
}
int main()
{
   real lambda, gamma, betta;
   FILE* file;
   fopen_s(&file, "grid.txt", "r");
   real* xgrid = new real[4];
   real* ygrid = new real[3];
   int* xsplitcount = new int[3];
   int* ysplitcount = new int[2];
   real* xcoef = new real[3];
   real* ycoef = new real[2];
   for (int i = 0; i <= 3; i++)
   {
      fscanf_s(file, "%f", &(xgrid[i]));
   }
   for (int i = 0; i <= 2; i++)
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
      fscanf_s(file, "%f", &(xcoef[i]));
   }
   for (int i = 0; i < 2; i++)
   {
      fscanf_s(file, "%f", &(ycoef[i]));
   }
   fscanf_s(file, "%f", &lambda);
   fscanf_s(file, "%f", &gamma);
   fscanf_s(file, "%f", &betta);
   fclose(file);

   fopen_s(&file, "BC.txt", "r");
   int* bctype = new int[8];
   for (int i = 0; i < 8; i++)
   {
      fscanf_s(file, "%d", &(bctype[i]));
   }
   fclose(file);
   int vertsx = 1;
   for (int i = 0; i < 3; i++)
   {
      vertsx += xsplitcount[i];
   }
   int vertsy = 1;
   for (int i = 0; i < 2; i++)
   {
      vertsy += ysplitcount[i];
   }
   int n = vertsx * vertsy;
   int m = vertsx;
   real** mat;
   real* b;
   mat = new real * [5];
   b = new real[n];

   for (int i = 0; i < 5; i++)
   {
      mat[i] = new real[n];
   }
   real* x0 = new real[n];//вектор решени€
   for (int i = 0; i < n; i++)
   {
      x0[i] = 0;
   }
   real dx[3];//длинна первого отрезка в сегменте
   real dy[2];
   for (int i = 0; i < 3; i++)
   {
      if (xcoef[i] == 1)
         dx[i] = (xgrid[i + 1] - xgrid[i]) / xsplitcount[i];
      else
         dx[i] = (xgrid[i + 1] - xgrid[i]) * (1 - xcoef[i]) / (1 - quickpower(xcoef[i], xsplitcount[i]));
   }

   for (int i = 0; i < 2; i++)
   {
      if (ycoef[i] == 1)
         dy[i] = (ygrid[i + 1] - ygrid[i]) / ysplitcount[i];
      else
         dy[i] = (ygrid[i + 1] - ygrid[i]) * (1 - ycoef[i]) / (1 - quickpower(ycoef[i], ysplitcount[i]));
   }
   real x;
   real y;

   //нижний р€д точек
   int index = 0;
   real hx0, hx1, hy0, hy1;
   mat[0][index] = 0;
   mat[1][index] = 0;
   mat[2][index] = 1;
   mat[3][index] = 0;
   mat[4][index] = 0;
   b[index] = 0;
   index += xsplitcount[0];
   if (bctype[0] == 1)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = BC(xgrid[1], ygrid[0], 0);
   }
   else
   {
      if (bctype[1] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[1], ygrid[0], 1);
      }
      else
      {
         hx1 = dx[1];
         mat[0][index] = 0;
         mat[1][index] = -lambda / hx1;
         mat[2][index] = lambda / hx1 + betta;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[1], ygrid[0], 1) * betta;
      }
   }
   index += xsplitcount[1];
   hx1 = dx[1] * quickpower(xcoef[1], xsplitcount[1] - 1);
   if (bctype[0] == 1)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = BC(xgrid[2], ygrid[0], 0);
   }
   else
   {
      if (bctype[2] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[2], ygrid[0], 2);
      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = lambda / hx1 + betta;
         mat[3][index] = -lambda / hx1;
         mat[4][index] = 0;
         b[index] = BC(xgrid[2], ygrid[0], 2) * betta;
      }
   }
   index += xsplitcount[2];
   mat[0][index] = 0;
   mat[1][index] = 0;
   mat[2][index] = 1;
   mat[3][index] = 0;
   mat[4][index] = 0;
   b[index] = 0;
   //средний р€д точек 
   index = ysplitcount[0] * m;
   hx1 = dx[0];
   if (bctype[4] == 1)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = BC(xgrid[0], ygrid[1], 4);
   }
   else
   {
      if (bctype[3] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[0], ygrid[1], 3);
      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = -lambda / hx1;
         mat[2][index] = lambda / hx1 + betta;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[0], ygrid[1], 4) * betta;
      }
   }
   index += xsplitcount[0];
   hx1 = dx[1];
   if (bctype[3] == 1)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = BC(xgrid[1], ygrid[1], 3);
   }
   else
   {
      if (bctype[1] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[1], ygrid[1], 1);
      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = -lambda / hx1;
         mat[2][index] = lambda / hx1 + betta;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[1], ygrid[1], 1) * betta;
      }
   }
   index += xsplitcount[1];
   hx1 *= quickpower(xcoef[1], xsplitcount[1] - 1);
   if (bctype[2] == 1)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = BC(xgrid[2], ygrid[1], 2);
   }
   else
   {
      if (bctype[7] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[2], ygrid[1], 7);
      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = lambda / hx1 + betta;
         mat[3][index] = -lambda / hx1;
         mat[4][index] = 0;
         b[index] = BC(xgrid[2], ygrid[1], 2) * betta;
      }
   }
   hy1 = dy[1];
   index += xsplitcount[2];
   if (bctype[6] == 1)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = BC(xgrid[3], ygrid[1], 6);
   }
   else
   {
      if (bctype[7] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[3], ygrid[1], 7);
      }
      else
      {
         mat[0][index] = -lambda / hy1;
         mat[1][index] = 0;
         mat[2][index] = lambda / hy1 + betta;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[3], ygrid[1], 7) * betta;
      }
   }
   //заполн€ем верхние точки
   index = (ysplitcount[0] + ysplitcount[1]) * m;
   hy1 = dy[1] * quickpower(ycoef[1], ysplitcount[1] - 1);
   if (bctype[4] == 1)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = BC(xgrid[0], ygrid[2], 4);
   }
   else
   {
      if (bctype[5] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[0], ygrid[2], 5);
      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = lambda / hy1 + betta;
         mat[3][index] = 0;
         mat[4][index] = -lambda / hy1;
         b[index] = BC(xgrid[0], ygrid[2], 5) * betta;
      }
   }
   index += xsplitcount[0];
   if (bctype[5] == 1)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = BC(xgrid[1], ygrid[2], 5);
   }
   else
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = lambda / hy1 + betta;
      mat[3][index] = 0;
      mat[4][index] = -lambda / hy1;
      b[index] = BC(xgrid[1], ygrid[2], 5) * betta;
   }
   index += xsplitcount[1];
   if (bctype[5] == 1)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = BC(xgrid[2], ygrid[2], 5);
   }
   else
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = lambda / hy1 + betta;
      mat[3][index] = 0;
      mat[4][index] = -lambda / hy1;
      b[index] = BC(xgrid[2], ygrid[2], 5) * betta;
   }
   index += xsplitcount[2];
   if (bctype[6] == 1)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = BC(xgrid[3], ygrid[2], 6);
   }
   else
   {
      if (bctype[5] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[3], ygrid[2], 5);
      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = lambda / hy1 + betta;
         mat[3][index] = 0;
         mat[4][index] = -lambda / hy1;
         b[index] = BC(xgrid[3], ygrid[2], 5) * betta;
      }
   }
   //заполн€ем внутренние точки
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 2; j++)
      {
         int index0 = 0;
         for (int k = 0; k < i; k++)
         {
            index0 += xsplitcount[k];
         }
         for (int k = 0; k < j; k++)
         {
            index0 += m * ysplitcount[k];
         }
         x = xgrid[i] + dx[i];
         hx0 = dx[i];
         hx1 = dx[i] * xcoef[i];
         for (int ix = 1; ix < xsplitcount[i]; ix++)
         {
            y = ygrid[j] + dy[j];
            hy0 = dy[j];
            hy1 = dy[j] * ycoef[j];
            for (int jy = 1; jy < ysplitcount[j]; jy++)
            {
               index = index0 + ix + m * jy;
               if (j == 0 && (i == 0 || i == 2))
               {
                  mat[0][index] = 0;
                  mat[1][index] = 0;
                  mat[2][index] = 1;
                  mat[3][index] = 0;
                  mat[4][index] = 0;
                  b[index] = 0;
               }
               else
               {
                  mat[0][index] = -lambda * 2 / hy1 / (hy1 + hy0);
                  mat[1][index] = -lambda * 2 / hx1 / (hx1 + hx0);
                  mat[2][index] = lambda * 2 * (1.0 / hx1 / hx0 + 1.0 / hy1 / hy0) + gamma;
                  mat[3][index] = -lambda * 2 / (hx0) / (hx1 + hx0);
                  mat[4][index] = -lambda * 2 / (hy0) / (hy1 + hy0);
                  b[index] = func(x, y);
               }
               y += hy1;
               hy0 = hy1;
               hy1 *= ycoef[j];
            }
            x += hx1;
            hx0 = hx1;
            hx1 *= ycoef[j];
         }

      }
   }
   //заполн€ем ребра
   index = 1;
   for (int i = 1; i < xsplitcount[0]; i++)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = 0;
      index++;
   }
   index = m;
   for (int i = 1; i < ysplitcount[0]; i++)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = 0;
      index += m;
   }
   index = xsplitcount[0] + xsplitcount[1] + 1;
   for (int i = 1; i < xsplitcount[2]; i++)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = 0;
      index += 1;
   }
   index = m + m - 1;
   for (int i = 1; i < ysplitcount[0]; i++)
   {
      mat[0][index] = 0;
      mat[1][index] = 0;
      mat[2][index] = 1;
      mat[3][index] = 0;
      mat[4][index] = 0;
      b[index] = 0;
      index += m;
   }
   //краевые услови€
   index = xsplitcount[0] + m;
   hx1 = dx[1];
   y = ygrid[0] + dy[0];
   hy1 = dy[0] * ycoef[0];
   for (int i = 1; i < ysplitcount[0]; i++)
   {
      if (bctype[1] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[1], y, 1);

      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = -lambda / hx1;
         mat[2][index] = lambda / hx1 + betta;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(x, ygrid[0], 1) * betta;
      }
      index += m;
      y += hy1;
      hy1 *= ycoef[0];
   }
   index = xsplitcount[0] + xsplitcount[1] + m;
   hx0 = dx[1] * quickpower(xcoef[1], xsplitcount[1] - 1);
   y = ygrid[0] + dy[0];
   hy1 = dy[0] * ycoef[0];
   for (int i = 1; i < ysplitcount[0]; i++)
   {
      if (bctype[2] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[2], y, 2);

      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = lambda / hx0 + betta;
         mat[3][index] = -lambda / hx0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[2], y, 2) * betta;
      }
      index += m;
      y += hy1;
      hy1 *= ycoef[0];
   }

   index = xsplitcount[0] + 1;
   hy1 = dy[0];
   x = xgrid[1] + dx[1];
   hx1 = dx[1] * xcoef[1];
   for (int i = 1; i < xsplitcount[1]; i++)
   {
      if (bctype[0] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(x, ygrid[0], 0);

      }
      else
      {
         mat[0][index] = -lambda / hy1;
         mat[1][index] = 0;
         mat[2][index] = lambda / hy1 + betta;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(x, ygrid[0], 0) * betta;
      }
      index += 1;
      x += hx1;
      hx1 *= xcoef[1];
   }

   index = ysplitcount[0] * m + 1;
   hy1 = dy[1];
   x = xgrid[0] + dx[0];
   hx1 = dx[0] * xcoef[0];
   for (int i = 1; i < xsplitcount[0]; i++)
   {
      if (bctype[3] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(x, ygrid[1], 3);

      }
      else
      {
         mat[0][index] = -lambda / hy1;
         mat[1][index] = 0;
         mat[2][index] = lambda / hy1 + betta;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(x, ygrid[1], 3) * betta;
      }
      index += 1;
      x += hx1;
      hx1 *= xcoef[0];
   }

   index = ysplitcount[0] * m + xsplitcount[0] + xsplitcount[1] + 1;
   hy1 = dy[1];
   x = xgrid[2] + dx[2];
   hx1 = dx[2] * xcoef[2];
   for (int i = 1; i < xsplitcount[2]; i++)
   {
      if (bctype[7] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(x, ygrid[1], 7);

      }
      else
      {
         mat[0][index] = -lambda / hy1;
         mat[1][index] = 0;
         mat[2][index] = lambda / hy1 + betta;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(x, ygrid[1], 7) * betta;
      }
      index += 1;
      x += hx1;
      hx1 *= xcoef[2];
   }

   index = (ysplitcount[0] + ysplitcount[1]) * m + 1;
   hy0 = dy[1] * quickpower(ycoef[1], ysplitcount[1] - 1);
   x = xgrid[0] + dx[0];
   hx1 = dx[0] * xcoef[0];
   for (int i = 1; i < xsplitcount[0]; i++)
   {
      if (bctype[5] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(x, ygrid[2], 5);

      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = lambda / hy0 + betta;
         mat[3][index] = 0;
         mat[4][index] = -lambda / hy0;
         b[index] = BC(x, ygrid[2], 5) * betta;
      }
      index += 1;
      x += hx1;
      hx1 *= xcoef[0];
   }
   x = xgrid[1];
   hx1 = dx[1];
   for (int i = 0; i < xsplitcount[1]; i++)
   {
      if (bctype[5] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(x, ygrid[2], 5);

      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = lambda / hy0 + betta;
         mat[3][index] = 0;
         mat[4][index] = -lambda / hy0;
         b[index] = BC(x, ygrid[2], 5) * betta;
      }
      index += 1;
      x += hx1;
      hx1 *= xcoef[1];
   }
   x = xgrid[2];
   hx1 = dx[2];
   for (int i = 0; i < xsplitcount[2]; i++)
   {
      if (bctype[5] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(x, ygrid[2], 5);

      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = lambda / hy0 + betta;
         mat[3][index] = 0;
         mat[4][index] = -lambda / hy0;
         b[index] = BC(x, ygrid[2], 5) * betta;
      }
      index += 1;
      x += hx1;
      hx1 *= xcoef[2];
   }

   index = ysplitcount[0] * m + m;
   hx1 = dx[0];
   y = ygrid[1] + dy[1];
   hy1 = dy[1] * ycoef[1];
   for (int i = 1; i < xsplitcount[2]; i++)
   {
      if (bctype[4] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[0], y, 4);

      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = -lambda / hx1;
         mat[2][index] = lambda / hx1 + betta;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[0], y, 4) * betta;
      }
      index += m;
      y += hy1;
      hy1 *= ycoef[1];
   }

   index = ysplitcount[0] * m + m - 1 + m;
   hx0 = dx[2] * quickpower(xcoef[2], xsplitcount[2] - 1);
   y = ygrid[1] + dy[1];
   hy1 = dy[1] * ycoef[1];
   for (int i = 1; i < ysplitcount[1]; i++)
   {
      if (bctype[6] == 1)
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = 1;
         mat[3][index] = 0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[3], y, 6);

      }
      else
      {
         mat[0][index] = 0;
         mat[1][index] = 0;
         mat[2][index] = lambda / hx0 + betta;
         mat[3][index] = -lambda / hx0;
         mat[4][index] = 0;
         b[index] = BC(xgrid[3], y, 6) * betta;
      }
      index += m;
      y += hy1;
      hy1 *= ycoef[1];
   }

   //заполн€ем внутренние ребра
   index = ysplitcount[0] * m + xsplitcount[0] + 1;
   hx1 = dx[1] * xcoef[1];
   hx0 = dx[1];
   hy1 = dy[1];
   hy0 = dy[0] * quickpower(ycoef[0], ysplitcount[0] - 1);
   y = ygrid[1];
   x = xgrid[1] + hx0;
   for (int i = 1; i < xsplitcount[1]; i++)
   {
      mat[0][index] = -lambda * 2 / hy1 / (hy1 + hy0);
      mat[1][index] = -lambda * 2 / hx1 / (hx1 + hx0);
      mat[2][index] = lambda * 2 * (1.0 / hx1 / hx0 + 1.0 / hy1 / hy0) + gamma;
      mat[3][index] = -lambda * 2 / (hx0) / (hx1 + hx0);
      mat[4][index] = -lambda * 2 / (hy0) / (hy1 + hy0);
      b[index] = func(x, y);
      x += hx1;
      hx0 = hx1;
      hx1 *= xcoef[1];
      index++;
   }

   index = ysplitcount[0] * m + xsplitcount[0] + m;
   hx1 = dx[1];
   hx0 = dx[0] * quickpower(xcoef[0], xsplitcount[0] - 1);
   hy1 = dy[1] * ycoef[1];
   hy0 = dy[1];
   y = ygrid[1] + hy0;
   x = xgrid[1];
   for (int i = 1; i < ysplitcount[1]; i++)
   {
      mat[0][index] = -lambda * 2 / hy1 / (hy1 + hy0);
      mat[1][index] = -lambda * 2 / hx1 / (hx1 + hx0);
      mat[2][index] = lambda * 2 * (1.0 / hx1 / hx0 + 1.0 / hy1 / hy0) + gamma;
      mat[3][index] = -lambda * 2 / (hx0) / (hx1 + hx0);
      mat[4][index] = -lambda * 2 / (hy0) / (hy1 + hy0);
      b[index] = func(x, y);
      y += hy1;
      hy0 = hy1;
      hy1 *= ycoef[1];
      index += m;
   }

   index = ysplitcount[0] * m + xsplitcount[0] + xsplitcount[1] + m;
   hx1 = dx[2];
   hx0 = dx[1] * quickpower(xcoef[1], xsplitcount[1] - 1);
   hy1 = dy[1] * ycoef[1];
   hy0 = dy[1];
   y = ygrid[1] + hy0;
   x = xgrid[2];
   for (int i = 1; i < ysplitcount[1]; i++)
   {
      mat[0][index] = -lambda * 2 / hy1 / (hy1 + hy0);
      mat[1][index] = -lambda * 2 / hx1 / (hx1 + hx0);
      mat[2][index] = lambda * 2 * (1.0 / hx1 / hx0 + 1.0 / hy1 / hy0) + gamma;
      mat[3][index] = -lambda * 2 / (hx0) / (hx1 + hx0);
      mat[4][index] = -lambda * 2 / (hy0) / (hy1 + hy0);
      b[index] = func(x, y);
      y += hy1;
      hy0 = hy1;
      hy1 *= ycoef[1];
      index += m;
   }



   real omega = 0.9;//коэфициент релаксации
   real precision = 1e-7;
   int maxiter = 100000;
   int k = SolveZeidelRelax(n, m, precision, maxiter, mat, b, x0, omega);
   index = ysplitcount[0] * m + m;
   for (int i = ysplitcount[0] + ysplitcount[1]; i >= ysplitcount[0]; i--)
   {
      for (int j = 0; j < m; j++)
      {
         printf_s("%f ", x0[i * m + j]);
      }
      printf_s("\n");
   }
   for (int i = ysplitcount[0] - 1; i >= 0; i--)
   {
      for (int j = xsplitcount[0]; j < xsplitcount[0] + xsplitcount[1] + 1; j++)
      {
         printf_s("%f ", x0[i * m + j]);
      }
      printf_s("\n");
   }
}

void JacobiIterationRelax(int n, int m, real** mat, real* b, real* x0, real* x, real omega)
{
   for (int i = 0; i < n; i++)
   {
      real cursumm = 0;
      if (i < n - m)
      {
         cursumm += mat[0][i] * x0[m + i];
      }
      if (i < n - 1)
      {
         cursumm += mat[1][i] * x0[i + 1];
      }
      cursumm += mat[2][i] * x0[i];
      if (i >= 1)
      {
         cursumm += mat[3][i] * x0[i - 1];
      }
      if (i >= 2 + m)
      {
         cursumm += mat[4][i] * x0[i - m];
      }
      x[i] = x0[i] + omega * (b[i] - cursumm) / mat[2][i];
   }
}


void MatrixMult(int n, int m, real** mat, real* x, real* b)//Ax=b
{
   for (int i = 0; i < n; i++)
   {
      b[i] = mat[2][i] * x[i];
   }
   for (int i = 0; i < n - m; i++)
   {
      b[i] += mat[0][i] * x[i + m];
   }
   for (int i = 0; i < n - 1; i++)
   {
      b[i] += mat[1][i] * x[i + 1];
   }
   for (int i = 1; i < n; i++)
   {
      b[i] += mat[3][i] * x[i - 1];
   }
   for (int i = m; i < n; i++)
   {
      b[i] += mat[4][i] * x[i - m];
   }
}

int SolveJacobiRelax(int n, int m, real precision, int maxiter, real** mat, real* b, real* x0, real* x, real omega)
{
   int k = 0;
   real relativeresidual = 1;
   real* curb;
   curb = new real[n];
   while (k < maxiter && relativeresidual > precision)
   {
      JacobiIterationRelax(n, m, mat, b, x0, x, omega);
      MatrixMult(n, m, mat, x, curb);
      real summ1 = 0, summ2 = 0;
      for (int i = 0; i < n; i++)
      {
         summ1 += (b[i] - curb[i]) * (b[i] - curb[i]);
         summ2 += b[i] * b[i];
         x0[i] = x[i];
      }
      relativeresidual = sqrt(summ1 / summ2);
      k++;
   }
   return k;
}

int  SolveZeidelRelax(int n, int m, real precision, int maxiter, real** mat, real* b, real* x0, real omega)
{
   int k = 0;
   real relativeresidual = 1;
   real* curb;
   curb = new real[n];
   while (k < maxiter && relativeresidual > precision)
   {
      JacobiIterationRelax(n, m, mat, b, x0, x0, omega);
      MatrixMult(n, m, mat, x0, curb);
      real summ1 = 0, summ2 = 0;
      for (int i = 0; i < n; i++)
      {
         summ1 += (b[i] - curb[i]) * (b[i] - curb[i]);
         summ2 += b[i] * b[i];
      }
      relativeresidual = sqrt(summ1 / summ2);
      k++;
   }
   return k;
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