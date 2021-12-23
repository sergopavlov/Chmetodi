#include "..\EugenValues\Eugen.h"
#include "Chmetodi4.h";
#include <stdio.h>
#include <cmath>
#include <vector>
#include "SFML/Graphics.hpp"
#include <sstream>

using namespace std;
using namespace sf;
vector<real(*)(real*, int, int, real)> funcs;
vector<vector<real(*)(real*, int)>> funcdiffs;
vector<int> nums1;
vector<int> nums2;
vector<real> vals;
vector<Vector2f> points;
real h;

int main()
{
   int n = 2, m = 2;
   real* x0 = new real[n];
   funcdiffs.resize(m);
   nums1.resize(m);
   vals.resize(m);
   nums2.resize(n);
   funcs.push_back(&cir11);
   funcs.push_back(&sinus);
   //funcs.push_back(&line33);

   //funcdiffs[0].push_back(&line3_1);
   //funcdiffs[0].push_back(&line3_2);
   //funcdiffs[1].push_back(&sinus_1);
   //funcdiffs[1].push_back(&sinus_2);
   //funcdiffs[2].push_back(&line33_1);
   //funcdiffs[2].push_back(&line33_2);

   x0[0] = 6;
   x0[1] = 1;
   h = 1e-7;
   int k = Newton2(n, m, x0, 1e-6, 1e-6, 10000);
   unsigned int width = 1000;
   unsigned int height = 700;
   RenderWindow window(VideoMode(width, height), "Newton? -Net Einshtein!");
   Font font;
   font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
   Vertex XAxis[] =
   {
      Vertex(Vector2f(50,height / 2.0)),
      Vertex(Vector2f(width - 50,height / 2.0))
   };
   for (int i = 0; i < 2; i++)
   {
      XAxis[i].color = Color::Black;
   }
   Vertex YAxis[] =
   {
      Vertex(Vector2f(width / 2.0,50)),
      Vertex(Vector2f(width / 2.0,height - 50))
   };
   for (int i = 0; i < 2; i++)
   {
      YAxis[i].color = Color::Black;
   }
   Vertex XMarks[20][2];
   Text Xtext[20];
   for (int i = 0; i < 10; i++)
   {
      Xtext[i].setString(to_string(-10 + i));
      Xtext[i].setFillColor(Color::Black);
      Xtext[i].setFont(font);
      Xtext[i].setCharacterSize(18);
      Xtext[i].move(Vector2f(50 - 15 + (width - 100) / 22.0 * (i + 1), height / 2.0 + 10));
      XMarks[i][0] = Vertex(Vector2f(50 + (width - 100) / 22.0 * (i + 1), height / 2.0 + 5));
      XMarks[i][0].color = Color::Black;
      XMarks[i][1] = Vertex(Vector2f(50 + (width - 100) / 22.0 * (i + 1), height / 2.0 - 5));
      XMarks[i][1].color = Color::Black;
      Xtext[19 - i].setString(to_string(10 - i));
      Xtext[19 - i].setFillColor(Color::Black);
      Xtext[19 - i].setFont(font);
      Xtext[19 - i].setCharacterSize(18);
      Xtext[19 - i].move(Vector2f(width - 50 - 7 - (width - 100) / 22.0 * (i + 1), height / 2 + 10));
      XMarks[19 - i][0] = Vertex(Vector2f(width - 50 - (width - 100) / 22.0 * (i + 1), height / 2 + 5));
      XMarks[19 - i][0].color = Color::Black;
      XMarks[19 - i][1] = Vertex(Vector2f(width - 50 - (width - 100) / 22.0 * (i + 1), height / 2 - 5));
      XMarks[19 - i][1].color = Color::Black;
   }
   Vertex YMarks[14][2];
   Text Ytext[14];
   for (int i = 0; i < 7; i++)
   {
      Ytext[i].setString(to_string(7 - i));
      Ytext[i].setFillColor(Color::Black);
      Ytext[i].setFont(font);
      Ytext[i].setCharacterSize(18);
      Ytext[i].move(Vector2f(width / 2.0 + 20, 50 - 10 + (height - 100) / 16.0 * (i + 1)));
      YMarks[i][0] = Vertex(Vector2f(width / 2.0 + 5, 50 + (height - 100) / 16.0 * (i + 1)));
      YMarks[i][0].color = Color::Black;
      YMarks[i][1] = Vertex(Vector2f(width / 2.0 - 5, 50 + (height - 100) / 16.0 * (i + 1)));
      YMarks[i][1].color = Color::Black;
      YMarks[13 - i][0] = Vertex(Vector2f(width / 2.0 + 5, height - 50 - (height - 100) / 16.0 * (i + 1)));
      YMarks[13 - i][0].color = Color::Black;
      YMarks[13 - i][1] = Vertex(Vector2f(width / 2.0 - 5, height - 50 - (height - 100) / 16.0 * (i + 1)));
      YMarks[13 - i][1].color = Color::Black;
      Ytext[13 - i].setString(to_string(i - 7));
      Ytext[13 - i].setFillColor(Color::Black);
      Ytext[13 - i].setFont(font);
      Ytext[13 - i].setCharacterSize(18);
      Ytext[13 - i].move(Vector2f(width / 2.0 + 15, height - 10 - 50 - (height - 100) / 16.0 * (i + 1)));
   }
   Text XAxisText;
   XAxisText.setString("X");
   XAxisText.setFillColor(Color::Black);
   XAxisText.setFont(font);
   XAxisText.setCharacterSize(18);
   XAxisText.move(Vector2f(width - 50 + 20, height / 2.0 - 10));
   Text YAxisText;
   YAxisText.setString("Y");
   YAxisText.setFillColor(Color::Black);
   YAxisText.setFont(font);
   YAxisText.setCharacterSize(18);
   YAxisText.move(Vector2f(width / 2.0 - 5, 50 - 40));

   CircleShape circle11(5);
   circle11.setOutlineThickness(0.05);
   circle11.setOutlineColor(Color::Blue);
   circle11.setFillColor(Color::Transparent);
   circle11.move(width / 2.0 - (5 + 4) * (width - 100) / 22.0, height / 2.0 - 5 * (height - 100) / 16.0);
   circle11.scale(Vector2f((width - 100) / 22.0, (height - 100) / 16.0));

   CircleShape circle12(5);
   circle12.setOutlineThickness(0.05);
   circle12.setOutlineColor(Color::Blue);
   circle12.setFillColor(Color::Transparent);
   circle12.move(width / 2.0 - 1 * (width - 100) / 22.0, height / 2.0 - 5 * (height - 100) / 16.0);
   circle12.scale(Vector2f((width - 100) / 22.0, (height - 100) / 16.0));


   CircleShape circle21(4);
   circle21.setOutlineThickness(0.05);
   circle21.setOutlineColor(Color::Blue);
   circle21.setFillColor(Color::Transparent);
   circle21.move(width / 2.0 - (4 + 4) * (width - 100) / 22.0, height / 2.0 - 4 * (height - 100) / 16.0);
   circle21.scale(Vector2f((width - 100) / 22.0, (height - 100) / 16.0));

   CircleShape circle22(4);
   circle22.setOutlineThickness(0.05);
   circle22.setOutlineColor(Color::Blue);
   circle22.setFillColor(Color::Transparent);
   circle22.move(width / 2.0 - (4 - 4) * (width - 100) / 22.0, height / 2.0 - (4) * (height - 100) / 16.0);
   circle22.scale(Vector2f((width - 100) / 22.0, (height - 100) / 16.0));

   CircleShape circle31(3);
   circle31.setOutlineThickness(0.05);
   circle31.setOutlineColor(Color::Blue);
   circle31.setFillColor(Color::Transparent);
   circle31.move(width / 2.0 - (3 + 4) * (width - 100) / 22.0, height / 2.0 - 3 * (height - 100) / 16.0);
   circle31.scale(Vector2f((width - 100) / 22.0, (height - 100) / 16.0));

   CircleShape circle32(3);
   circle32.setOutlineThickness(0.05);
   circle32.setOutlineColor(Color::Blue);
   circle32.setFillColor(Color::Transparent);
   circle32.move(width / 2.0 + (width - 100) / 22.0, height / 2.0 - (3) * (height - 100) / 16.0);
   circle32.scale(Vector2f((width - 100) / 22.0, (height - 100) / 16.0));

   Vertex Line1plot[] =
   {
      Vertex(Vector2f(width / 2.0 - 3 * (width - 100) / 22.0,height / 2.0)),
      Vertex(Vector2f(width / 2.0 + 3 * (width - 100) / 22.0,height / 2.0 - 6 * (height - 100) / 16.0))
   };
   Line1plot[0].color = Color::Blue;
   Line1plot[1].color = Color::Blue;

   Vertex Line2plot[] =
   {
      Vertex(Vector2f(width / 2.0 - 3 * (width - 100) / 22.0,height / 2.0 + 3 * (height - 100) / 16.0)),
      Vertex(Vector2f(width / 2.0 + 3 * (width - 100) / 22.0,height / 2.0 - 3 * (height - 100) / 16.0))
   };
   Line2plot[0].color = Color::Blue;
   Line2plot[1].color = Color::Blue;

   Vertex Line31plot[] =
   {
      Vertex(Vector2f(width / 2.0 - 7 * (width - 100) / 22.0,height / 2.0 + 0 * (height - 100) / 16.0)),
      Vertex(Vector2f(width / 2.0 + 7 * (width - 100) / 22.0,height / 2.0 - 0 * (height - 100) / 16.0))
   };
   Line31plot[0].color = Color::Blue;
   Line31plot[1].color = Color::Blue;

   Vertex Line32plot[] =
   {
      Vertex(Vector2f(width / 2.0 - 0 * (width - 100) / 22.0,height / 2.0 + 6 * (height - 100) / 16.0)),
      Vertex(Vector2f(width / 2.0 + 0 * (width - 100) / 22.0,height / 2.0 - 6 * (height - 100) / 16.0))
   };
   Line32plot[0].color = Color::Blue;
   Line32plot[1].color = Color::Blue;

   Vertex Line33plot[] =
   {
      Vertex(Vector2f(width / 2.0 - 3 * (width - 100) / 22.0,height / 2.0 - 4 * (height - 100) / 16.0)),
      Vertex(Vector2f(width / 2.0 + 3 * (width - 100) / 22.0,height / 2.0 + 2 * (height - 100) / 16.0))
   };
   Line33plot[0].color = Color::Blue;
   Line33plot[1].color = Color::Blue;

   vector<CircleShape> Xpoints(points.size());
   for (int i = 0; i < points.size(); i++)
   {
      Xpoints[i] = CircleShape(4);
      Xpoints[i].setFillColor(Color::Magenta);
      Xpoints[i].move(width / 2.0 - 4 + (points[i].x) * (width - 100) / 22.0, height / 2.0 - 4 - (points[i].y) * (height - 100) / 16.0);
   }
   Xpoints[0].setFillColor(Color::Red);
   vector<Vertex[2]> Xvectors(points.size() - 1);
   for (int i = 0; i < points.size() - 1; i++)
   {
      Xvectors[i][0] = Vertex(Vector2f(width / 2.0 + (points[i].x) * (width - 100) / 22.0, height / 2.0 - (points[i].y) * (height - 100) / 16.0));
      Xvectors[i][0].color = Color::Black;
      Xvectors[i][1] = Vertex(Vector2f(width / 2.0 + (points[i + 1].x) * (width - 100) / 22.0, height / 2.0 - (points[i + 1].y) * (height - 100) / 16.0));
      Xvectors[i][1].color = Color::Black;
   }

   Vertex sinplot[1000];
   for (int i = 0; i < 1000; i++)
   {
      sinplot[i] = Vertex(Vector2f(width / 2.0 + (-10 + 20.0 / 1000 * i) * (width - 100) / 22.0, height / 2.0 - (sin(-10 + 20.0 / 1000 * i)+2) * (height - 100) / 16.0));
      sinplot[i].color = Color::Blue;
   }
   while (window.isOpen())
   {
      Event event;
      while (window.pollEvent(event))
      {
         if (event.type == Event::Closed)
            window.close();
      }
      window.clear(Color::White);
      window.draw(XAxis, 2, Lines);
      window.draw(YAxis, 2, Lines);
      for (int i = 0; i < 20; i++)
      {
         window.draw(Xtext[i]);
         window.draw(XMarks[i], 2, Lines);
      }
      window.draw(XAxisText);
      for (int i = 0; i < 14; i++)
      {
         window.draw(YMarks[i], 2, Lines);
         window.draw(Ytext[i]);
      }
      window.draw(YAxisText);
      //window.draw(circle11);
      window.draw(circle12);
      //window.draw(circle21);
      //window.draw(circle22);
      //window.draw(circle31);
      //window.draw(circle32);
      //window.draw(Line1plot, 2, Lines);
      //window.draw(Line2plot, 2, Lines);
      //window.draw(Line31plot, 2, Lines);
      //window.draw(Line32plot, 2, Lines);
      //window.draw(Line33plot, 2, Lines);
      window.draw(sinplot, 1000, LinesStrip);
      for (int i = 0; i < points.size() - 1; i++)
      {
         window.draw(Xvectors[i], 2, Lines);
      }
      for (int i = 0; i < points.size(); i++)
      {
         window.draw(Xpoints[i]);
      }
      window.display();
   }
   printf_s("asdasd");
}

void CalculateMinusF2(real* f, real* x, int n, int m)
{
   f[0] = -funcs[0](x, n, -1, h);
   nums2[0] = 0;
   for (int i = 1; i < m; i++)
   {
      real cur = -funcs[i](x, n, -1, h);
      int jbeg = min(i - 1, n - 1);
      bool flag = true;
      for (int j = jbeg; j >= 0; j--)
      {
         if (j == n - 1)
         {
            if (abs(f[j]) > abs(cur))
            {
               flag = false;
            }
         }
         else
         {
            if (abs(f[j]) > abs(cur))
            {
               f[j + 1] = cur;
               nums2[j + 1] = i;
               flag = false;
            }
            else
            {
               f[j + 1] = f[j];
               nums2[j + 1] = nums2[j];
               if (j == 0)
               {
                  f[0] = cur;
                  nums2[0] = i;
               }
            }
         }
      }
   }
}

real CalculateNormF(real* x, int m)
{
   real summ = 0;
   for (int i = 0; i < m; i++)
   {
      summ += funcs[i](x, m, -1, h) * funcs[i](x, m, -1, h);
   }
   return sqrt(summ);
}

void CalculateJacobi2(real** J, real* x, int n, int m)
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         J[i][j] = funcdiffs[nums2[i]][j](x, n);
      }
   }
}

void CalculateJacobinum2(real** J, real* x, int n, int m)
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         J[i][j] = (funcs[nums2[i]](x, n, j, h) - funcs[nums2[i]](x, n, j, -h)) / (2 * h);
      }
   }
}

int Newton1(int n, int m, real* x0, real eps1, real eps2, int maxiter)//n>m
{
   real** J = new real * [m];
   real* F = new real[m];
   real* Fnext = new real[m];
   real* xnext = new real[n];
   real Fnormnext;
   real Fnorm;
   real b;
   bool flagnotend = true;
   for (int i = 0; i < m; i++)
   {
      J[i] = new real[m];
   }
   real F0 = CalculateNormF(x0, m);
   int k = 0;
   while (flagnotend && k < maxiter)
   {
      CalculateJacobi1(J, x0, n, m);
      CalculateMinusF1(F, x0, n, m);
      Fnorm = CalculateNormF(x0, m);
      SolveSlae(J, F, m);
      b = 1;
      bool flag = true;
      while (flagnotend && flag)
      {
         for (int i = 0; i < n; i++)
         {
            xnext[i] = x0[i];
         }
         for (int i = 0; i < m; i++)
         {
            xnext[nums1[i]] += b * F[i];
         }
         Fnormnext = CalculateNormF(xnext, m);
         if (Fnormnext < Fnorm)
         {
            flag = false;
         }
         b /= 2;
         if (b < eps1)
            flagnotend = false;
      }
      for (int i = 0; i < n; i++)
      {
         x0[i] = xnext[i];
      }
      if (Fnormnext / F0 < eps2)
         flagnotend = false;
      k++;
   }
   return k;
}

void CalculateJacobi1(real** J, real* x, int n, int m)
{
   for (int i = 0; i < m; i++)
   {
      J[i][0] = funcdiffs[i][0](x, n);
      if (abs(J[i][0]) > vals[0])
         vals[0] = abs(J[0][i]);
   }
   nums1[0] = 0;
   for (int i = 1; i < n; i++)
   {
      real curval = 0;
      real* cur = new real[m];
      for (int j = 0; j < m; j++)
      {
         cur[j] = funcdiffs[j][i](x, n);
         if (abs(cur[i]) > curval)
            curval = abs(cur[i]);
      }
      int jbeg = min(i - 1, n - 1);
      bool flag = true;

      for (int j = jbeg; j >= 0; j--)
      {
         if (j == n - 1)
         {
            if (vals[j] > curval)
            {
               flag = false;
            }
         }
         else
         {
            if (vals[j] > curval)
            {
               for (int k = 0; k < m; k++)
               {
                  J[j + 1][k] = cur[k];
               }
               nums2[j + 1] = i;
               flag = false;
            }
            else
            {
               for (int k = 0; k < m; k++)
               {
                  J[j + 1][k] = J[j][k];
               }
               nums2[j + 1] = nums2[j];
               if (j == 0)
               {
                  for (int k = 0; k < m; k++)
                  {
                     J[0][k] = cur[k];
                  }
                  nums2[0] = i;
               }
            }
         }
      }
   }
}

void CalculateMinusF1(real* f, real* x, int n, int m)
{
   for (int i = 0; i < m; i++)
   {
      f[i] = -funcs[i](x, n, -1, h);
   }
}

int Newton2(int n, int m, real* x0, real eps1, real eps2, int maxiter)//m уравнений n  неизвестных n<m
{
   real** J = new real * [n];
   real* F = new real[n];
   real* Fnext = new real[n];
   real* xnext = new real[n];
   real Fnormnext;
   real Fnorm;
   real b;
   bool flagnotend = true;
   for (int i = 0; i < n; i++)
   {
      J[i] = new real[n];
   }
   real F0 = CalculateNormF(x0, m);
   int k = 0;
   points.push_back(Vector2f(x0[0], x0[1]));
   while (flagnotend && k < maxiter)
   {
      CalculateMinusF2(F, x0, n, m);
      CalculateJacobinum2(J, x0, n, m);
      Fnorm = CalculateNormF(x0, m);
      SolveSlae(J, F, n);
      b = 1;
      bool flag = true;
      while (flagnotend && flag)
      {
         if (b < eps1)
            flagnotend = false;
         for (int i = 0; i < n; i++)
         {
            xnext[i] = x0[i] + b * F[i];
         }
         Fnormnext = CalculateNormF(xnext, m);
         if (Fnormnext < Fnorm)
         {
            flag = false;
         }
         b /= 2;
      }
      for (int i = 0; i < n; i++)
      {
         x0[i] = xnext[i];
      }
      printf_s("iteration number: %d\nbetta: %e\n Fnorm: %e\nx: ", k + 1, b, Fnormnext);
      for (int i = 0; i < n; i++)
      {
         printf_s("%f ", x0[i]);
      }
      printf_s("\n-------------------\n");
      points.push_back(Vector2f(x0[0], x0[1]));
      if (Fnormnext / F0 < eps2)
         flagnotend = false;
      k++;
   }
   return k;
}

void SolveSlae(real** A, real* b, int n)
{
   for (int i = 0; i < n; i++)
   {
      real summd = 0;
      for (int j = 0; j < i; j++)
      {
         real summl = 0;
         real summu = 0;
         for (int k = 0; k < j; k++)
         {
            summl += A[i][k] * A[k][j];
            summu += A[j][k] * A[k][i];
         }
         A[i][j] -= summl;
         A[j][i] = (A[j][i] - summu) / A[j][j];
         summd += A[i][j] * A[j][i];
      }
      A[i][i] -= summd;
   }
   for (int i = 0; i < n; i++)
   {
      real summ = 0;
      for (int j = 0; j < i; j++)
      {
         summ += A[i][j] * b[j];
      }
      b[i] = (b[i] - summ) / A[i][i];
   }
   for (int i = n - 1; i >= 0; i--)
   {
      real summ = 0;
      for (int j = n - 1; j > i; j--)
      {
         summ += A[i][j] * b[j];
      }
      b[i] -= summ;
   }
}
void MatrixMult(real** A, real* x, real* b, int n)
{
   for (int i = 0; i < n; i++)
   {
      b[i] = 0;
      for (int j = 0; j < n; j++)
      {
         b[i] += A[i][j] * x[j];
      }
   }
}
void LUfactorization(int n, int* ia, real* di, real* au, real* al)
{
   for (int i = 0; i < n; i++)
   {
      real sumrow = 0;
      int j0 = i - (ia[i + 1] - ia[i]);
      int dind = j0;
      for (int ii = ia[i]; ii < ia[i + 1]; ii++, dind++)
      {
         int j = j0 + ii - ia[i];
         int j0j = j - (ia[j + 1] - ia[j]);

         int kbeg = j0 > j0j ? j0 : j0j;
         int kend = i > j ? j : i;
         real summu = 0;
         real summl = 0;
         int indexi = ia[i] + kbeg - j0;
         int indexj = ia[j] + kbeg - j0j;
         for (int k = 0; k < kend - kbeg; k++, indexi++, indexj++)
         {
            summu += al[indexj] * au[indexi];
            summl += al[indexi] * au[indexj];
         }
         al[ii] -= summl;
         au[ii] = (au[ii] - summu) / di[j];
         sumrow += au[ii] * al[ii];
      }
      di[i] -= sumrow;
   }
}

real cir11(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = (x[0] - 4) * (x[0] - 4) + x[1] * x[1] - 25;
   else
   {
      x[j] += h;
      res = (x[0] - 4) * (x[0] - 4) + x[1] * x[1] - 25;
      x[j] -= h;
   }
   return res;
}

real cir12(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = (x[0] + 4) * (x[0] + 4) + x[1] * x[1] - 25;
   else
   {
      x[j] += h;
      res = (x[0] + 4) * (x[0] + 4) + x[1] * x[1] - 25;
      x[j] -= h;
   }
   return res;
}

real line3(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = x[1] - x[0] - 3;
   else
   {
      x[j] += h;
      res = x[1] - x[0] - 3;
      x[j] -= h;
   }
   return res;
}

real cir21(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = (x[0] - 4) * (x[0] - 4) + x[1] * x[1] - 16;
   else
   {
      x[j] += h;
      res = (x[0] - 4) * (x[0] - 4) + x[1] * x[1] - 16;
      x[j] -= h;
   }
   return res;
}

real cir22(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = (x[0] + 4) * (x[0] + 4) + x[1] * x[1] - 16;
   else
   {
      x[j] += h;
      res = (x[0] + 4) * (x[0] + 4) + x[1] * x[1] - 16;
      x[j] -= h;
   }
   return res;
}

real line2(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = x[1] - x[0];
   else
   {
      x[j] += h;
      res = x[1] - x[0];
      x[j] -= h;
   }
   return res;
}

real cir31(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = (x[0] - 4) * (x[0] - 4) + x[1] * x[1] - 9;
   else
   {
      x[j] += h;
      res = (x[0] - 4) * (x[0] - 4) + x[1] * x[1] - 9;
      x[j] -= h;
   }
   return res;
}

real cir32(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = (x[0] + 4) * (x[0] + 4) + x[1] * x[1] - 9;
   else
   {
      x[j] += h;
      res = (x[0] + 4) * (x[0] + 4) + x[1] * x[1] - 9;
      x[j] -= h;
   }
   return res;
}

real line31(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = x[0];
   else
   {
      x[j] += h;
      res = x[0];
      x[j] -= h;
   }
   return res;
}

real line32(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = 2 * x[1];
   else
   {
      x[j] += h;
      res = 2 * x[1];
      x[j] -= h;
   }
   return res;
}

real line33(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = 5 * (x[0] + x[1] - 1);
   else
   {
      x[j] += h;
      res = 5 * (x[0] + x[1] - 1);
      x[j] -= h;
   }
   return res;
}

real sinus(real* x, int n, int j, real h)
{
   real res;
   if (j == -1)
      res = x[1] - sin(x[0])-2;
   else
   {
      x[j] += h;
      res = x[1] - sin(x[0])-2;
      x[j] -= h;
   }
   return res;
}

real cir11_1(real* x, int n)
{
   return 2 * (x[0] - 4);
}

real cir11_2(real* x, int n)
{
   return 2 * x[1];
}

real cir12_1(real* x, int n)
{
   return 2 * (x[0] + 4);
}

real cir12_2(real* x, int n)
{
   return 2 * x[1];
}

real cir21_1(real* x, int n)
{
   return 2 * (x[0] - 4);
}

real cir21_2(real* x, int n)
{
   return 2 * x[1];
}

real cir22_1(real* x, int n)
{
   return 2 * (x[0] + 4);
}

real cir22_2(real* x, int n)
{
   return 2 * x[1];
}

real line3_1(real* x, int n)
{
   return -1;
}

real line3_2(real* x, int n)
{
   return 1;
}

real line2_1(real* x, int n)
{
   return -1;
}

real line2_2(real* x, int n)
{
   return 1;
}

real line31_1(real* x, int n)
{
   return 1;
}

real line31_2(real* x, int n)
{
   return 0;
}

real line32_1(real* x, int n)
{
   return 0;
}

real line32_2(real* x, int n)
{
   return 2;
}

real line33_1(real* x, int n)
{
   return 5;
}

real line33_2(real* x, int n)
{
   return 5;
}

real sinus_1(real* x, int n)
{
   return cos(x[0]);
}
real sinus_2(real* x, int n)
{
   return 1;
}