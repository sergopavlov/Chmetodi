#include<stdio.h>
#include "umf1.h"
int main()
{
	int n, m, k;
	inputparams(&n, &m, &k);
	real* xsec = new real[n];
	real* ysec = new real[m];
	int* xsecsplitcount = new int[n - 1];
	int* ysecsplitcount = new int[m - 1];
	real* xdischargeratio = new real[n - 1];
	real* ydischargeratio = new real[m - 1];
	bool* subareas = new bool[(n-1)*(m-1)];
	input(n, m, k, xsec, ysec, xsecsplitcount, ysecsplitcount, xdischargeratio, ydischargeratio,subareas);
	printf_s("sosi trak");
}

void inputparams(int* n, int* m, int* k)
{
	FILE* file;
	fopen_s(&file, "dims.txt", "r");
	fscanf_s(file, "%d %d %d", n, m, k);
	fclose(file);
}

void input(int n, int m, int k, real* xsec, real* ysec, int* xsecsplitcount, int* ysecsplitcount, real* xdischargeratio, real* ydischargeratio,bool* subareas)
{
	FILE* file;
	fopen_s(&file, "grid.txt", "r");
	for (int i = 0; i < n; i++)
	{
		fscanf_s(file, "%f", &(xsec[i]));
	}
	for (int i = 0; i < m; i++)
	{
		fscanf_s(file, "%f", &(ysec[i]));
	}
	for (int i = 0; i < (n-1)*(m-1); i++)
	{
		fscanf_s(file, "%d", &(subareas[i]));
	}
	for (int i = 0; i < n-1; i++)
	{
		fscanf_s(file, "%d", &(xsecsplitcount[i]));
	}
	for (int i = 0; i < m-1; i++)
	{
		fscanf_s(file, "%d", &(ysecsplitcount[i]));
	}
	for (int i = 0; i < n-1; i++)
	{
		fscanf_s(file, "%f", &(xdischargeratio[i]));
	}
	for (int i = 0; i < m-1; i++)
	{
		fscanf_s(file, "%f", &(ydischargeratio[i]));
	}
	fclose(file);
}