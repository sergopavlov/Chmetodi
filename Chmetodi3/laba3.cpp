#include <stdio.h>
#include "laba3.h"
#include <cmath>
#include <time.h>

int main()
{
	int n, m, maxiter;
	real eps;
	inputparams(&n, &m, &maxiter, &eps);

	//n = 1000;
	//m = (n - 1) * n / 2;
	int* ia = new int[n + 1];
	int* ja = new int[m];
	real* di = new real[n];
	real* al = new real[m];
	real* x = new real[n];
	real* x0 = new real[n];
	real* b = new real[n];
	real* xtrue = new real[n];
	/*ia[0] = 0;
	for (int i = 1; i < n + 1; i++)
	{
		ia[i] = ia[i - 1] + i - 1;
	}
	for (int i = 0; i < n; i++)
	{
		for (int k = ia[i]; k < ia[i + 1]; k++)
		{
			ja[k] = k - ia[i];
		}
	}*/

	for (int i = 0; i < n; i++)
	{
		x0[i] = 0;
		x[i] = i + 1;
	}
	input(ia, ja, di, al, x0, b, n, m);
	//generategilbert(n, ia, ja, di, al);
	MatrixMult(ia, ja, n, al, di, x, b);
	
	clock_t start, end;
	start = clock();
	int k = MSG(ia, ja, n, al, di, x0, b, maxiter, eps);
	end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	printf_s("%d %lf \n", k, time);

	for (int i = 0; i < n; i++)
	{
		x0[i] = 0;
		x[i] = i + 1;
	}
	
	start = clock();

	k = LOS(ia, ja, n, al, di, x0, b, maxiter, eps);

	end = clock();
	double time2 = (double)((end - start) / CLOCKS_PER_SEC);
	printf_s("%d time: %lf \n", k, time2);
}

void inputparams(int* n, int* m, int* maxiter, real* eps)
{
	FILE* file;
	fopen_s(&file, "params.txt", "r");
	fscanf_s(file, "%d %d %d %lf", n, m, maxiter, eps);
	fclose(file);
}

void generategilbert(int n, int* ia, int* ja, real* di, real* al)
{
	for (int i = 0; i < n; i++)
	{
		di[i] = 1.0 / (2 * i + 1);
		for (int k = ia[i]; k < ia[i + 1]; k++)
		{
			al[k] = 1.0 / (i + ja[k] + 1);
		}
	}
}

void input(int* ia, int* ja, real* di, real* al, real* x0, real* b, int n, int m)
{
	FILE* file;
	fopen_s(&file, "ia.txt", "r");
	for (int i = 0; i < n + 1; i++)
	{
		fscanf_s(file, "%d", &ia[i]);
	}
	fclose(file);

	fopen_s(&file, "ja.txt", "r");
	for (int i = 0; i < m; i++)
	{
		fscanf_s(file, "%d", &ja[i]);
	}
	fclose(file);

	fopen_s(&file, "al.txt", "r");
	for (int i = 0; i < m; i++)
	{
		fscanf_s(file, "%lf", &al[i]);
	}
	fclose(file);

	fopen_s(&file, "di.txt", "r");
	for (int i = 0; i < n; i++)
	{
		fscanf_s(file, "%lf", &di[i]);
	}
	fclose(file);

	fopen_s(&file, "x0.txt", "r");
	for (int i = 0; i < n; i++)
	{
		fscanf_s(file, "%lf", &x0[i]);
	}
	fclose(file);

	fopen_s(&file, "b.txt", "r");
	/*for (int i = 0; i < n; i++)
	{
	   fscanf_s(file, "%lf", &b[i]);
	}
	fclose(file);*/
}

int MSG(int* ia, int* ja, int n, real* al, real* di, real* x, real* b, int maxiter, real eps)
{
	real bnorm = sqrt(DotProduct(b, b, n));
	real* r = new real[n];
	real* p = new real[n];
	real* q = new real[n];
	MatrixMult(ia, ja, n, al, di, x, r);
	for (int i = 0; i < n; i++)
	{
		r[i] = b[i] - r[i];
		p[i] = r[i];
	}
	int k = 0;
	real alpha, betta, rnorm = sqrt(DotProduct(r, r, n));
	while (k<maxiter && rnorm / bnorm>eps)
	{
		MatrixMult(ia, ja, n, al, di, p, q);
		alpha = DotProduct(r, r, n) / DotProduct(q, p, n);
		betta = 1 / DotProduct(r, r, n);
		for (int i = 0; i < n; i++)
		{
			x[i] += alpha * p[i];
			r[i] -= alpha * q[i];
		}
		rnorm = sqrt(DotProduct(r, r, n));
		betta *= rnorm * rnorm;
		for (int i = 0; i < n; i++)
		{
			p[i] = r[i] + betta * p[i];
		}
		k++;
	}
	printf_s("relative residual is: %e\n", rnorm / bnorm);
	return k;
}

int LOS(int* ia, int* ja, int n, real* al, real* di, real* x, real* b, int maxiter, real eps)
{
	real bnorm = sqrt(DotProduct(b, b, n));
	real* r = new real[n];
	real* p = new real[n];
	real* z = new real[n];
	real* Ar = new real[n];
	MatrixMult(ia, ja, n, al, di, x, r);
	for (int i = 0; i < n; i++)
	{
		r[i] = b[i] - r[i];
		z[i] = r[i];
	}
	MatrixMult(ia, ja, n, al, di, z, p);
	int k = 0;
	real alpha, betta, rnorm = sqrt(DotProduct(r, r, n));
	while (k<maxiter && rnorm / bnorm>eps)
	{
		alpha = DotProduct(p, r, n) / DotProduct(p, p, n);
		for (int i = 0; i < n; i++)
		{
			x[i] += alpha * z[i];
			r[i] -= alpha * p[i];
		}
		MatrixMult(ia, ja, n, al, di, r, Ar);
		betta = -DotProduct(p, Ar, n) / DotProduct(p, p, n);
		rnorm = sqrt(DotProduct(r, r, n));
		for (int i = 0; i < n; i++)
		{
			z[i] = r[i] + betta * z[i];
			p[i] = Ar[i] + betta * p[i];
		}
		k++;
	}
	printf_s("relative residual is: %e\n", rnorm / bnorm);
	return k;
}


real DotProduct(real* x, real* y, int n)
{
	real res = 0;
	for (int i = 0; i < n; i++)
	{
		res += x[i] * y[i];
	}
	return res;
}

void MatrixMult(int* ia, int* ja, int n, real* al, real* di, real* x, real* b)
{
	for (int i = 0; i < n; i++)
	{
		b[i] = x[i] * di[i];
		for (int k = ia[i]  ; k < ia[i + 1]; k++)
		{
			int j = ja[k] ;
			b[i] += al[k] * x[j];
			b[j] += al[k] * x[i];
		}
	}
}