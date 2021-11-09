#include <stdio.h>
#include "Splain.h"
#include <cmath>



int main()
{
   int n = 11;
   real* grid = new real[n];
   real h = 0.5;
   for (int i = 0; i < n; i++)
   {
      grid[i] = i * 0.5;
   }
   real* f = new real[n];
   real* q = new real[2 * n];
   getfuncarray(n, f, grid);
   splain(grid, f, q, n);
   real curx = 0;
   for (int i = 0; i < 4*(n-1)+1; i++)
   {
      printf_s("%f %f %f %f\n",curx, getsollution(curx, n, grid, q), func(curx), fabs(func(curx) - getsollution(curx, n, grid, q)));
      curx += 0.125;
   }
}

void splain(real* grid, real* f, real* q, int n)
{
   q[0] = f[0];
   q[1] = (f[1] - f[0]) / (grid[1] - grid[0]);
   for (int i = 1; i < n; i++)
   {
      q[2 * i] = f[i];
      q[2 * i + 1] = (f[i + 1] - f[i - 1]) / (grid[i + 1] - grid[i - 1]);
   }
   q[2 * n - 2] = f[n - 1];
   q[2 * n - 1] = (f[n - 1] - f[n - 2]) / (grid[n - 1] - grid[n - 2]);
}

real getsollution(real x, int n, real* grid, real* q)
{
   if (x > grid[n - 1] || x < grid[0])
      return NAN;
   int left = 0;
   int right = n - 1;
   int cur = n / 2;
   while (right - left > 1)
   {
      if (x > grid[cur])
         left = cur;
      else
         right = cur;
      cur = (left + right) / 2;
   }
   real h = (grid[right] - grid[left]);
   real t = (x - grid[left]) / h;
   real res = 0;
   res += q[2 * left] * 2 * (t + 0.5) * (t - 1) * (t - 1);
   res += q[2 * left + 1] * t * (t - 1) * (t - 1) * h;
   res += q[2 * right] * (-2) * t * t * (t - 1.5);
   res += q[2 * right + 1] * t * t * (t - 1) * h;
   return res;
}

void getfuncarray(int n, real* f, real* grid)
{
   for (int i = 0; i < n; i++)
   {
      f[i] = func(grid[i]);
   }
}
real  func(real x)
{
   return x * x * x;
}