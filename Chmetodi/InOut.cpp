#include "SolveSLAE.h"
#include "iostream"
#include "InOut.h"

void getdims(int* n, int* m)
{
	FILE* in;
	fopen_s(&in, "dims.txt", "r");
	fscanf_s(in, "%d,%d", n, m);
	fclose(in);
}

void input(real* Al, real* Di, real* b, int* Ia, int n, int m)
{
	FILE* in;
	fopen_s(&in, "Al.txt", "r");
	for (int i = 0; i < m; i++)
	{
		fscanf_s(in, str2, &(Al[i]));
	}
	fclose(in);

	fopen_s(&in, "Di.txt", "r");
	for (int i = 0; i < n; i++)
	{
		fscanf_s(in, str2, &(Di[i]));
	}
	fclose(in);
	fopen_s(&in, "Ia.txt", "r");
	for (int i = 0; i < n + 1; i++)
	{
		fscanf_s(in, "%d", &(Ia[i]));
	}
}
   fopen_s(&in, "b.txt", "r");
   for (int i = 0; i < n; i++)
   {
      fscanf_s(in, str2, &(b[i]));
   }
   fclose(in);

   fopen_s(&in, "Ia.txt", "r");
   for (int i = 0; i <= n; i++)
   {
      fscanf_s(in, "%d", &(Ia[i]));
   }
   fclose(in);
}

void output(real* x, int n)
{
	FILE* out;
	fopen_s(&out, "out.txt", "w");
	for (int i = 0; i < n; i++)
	{
		fprintf_s(out, "%f", x[i]);
	}
	fclose(out);
}