#include <stdio.h>
#include "Splain.h"



int main()
{
	int n = 5;
	real* grid = new real[n];
	for (int i = 0; i < n; i++)
	{
		grid[i] = i;
	}
	real res = getsollution(2.5, n, grid, nullptr);
	printf_s("%f", res);
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
	res += q[2 * left] * 2 * (t + 0.5)(t - 1) * (t - 1);
	res += q[2 * left + 1] * t * (t - 1) * (t - 1) / h;//h??
}