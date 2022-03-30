#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Splain.h"
#include <math.h>
#include <string>
#include <sstream>
/*Привет от Сергея Павлова*/

# define M_PI     3.14159265358979323846
using namespace sf;

int main()
{
   int tochki = 5;
   int n = 6;
   int m = tochki * (n - 1);
   real* x = new real[m];
   real* y = new real[m];
   real* grid = new real[n];
   real h = 2;
   for (int i = 0; i < n; i++)
   {
      grid[i] = i * h;
      for (int j = 0; j < tochki; j++)
      {
         x[i * tochki + j] = grid[i] + (j + 1) * h / (tochki + 1);
      }
   }
   getfuncarray(m, y, x);
   real eps = 0.5;
   for (int i = 0; i < m; i++)
   {
      y[i] += eps;
      eps *= -1;
   }
   real* f = new real[n];
   real* q = new real[2 * n];
   getfuncarray(n, f, grid);
   real minf = f[0], maxf = f[0];
   for (int i = 1; i < n; i++)
   {
      if (f[i] > maxf)
         maxf = f[i];
      if (f[i] < minf)
         minf = f[i];
   }
   SSplain(grid, q, n, x, y, m, 0, 1e3);
   //ISplain(grid, f, q, n);
   Font font;
   font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
   int plotparameter = 500;
   ContextSettings settings;
   settings.antialiasingLevel = 7;
   unsigned int xwidth = 750;
   unsigned int ywidth = 500;

   RenderWindow window(VideoMode(xwidth, ywidth), "Splain!", Style::Default, settings);
   while (window.isOpen())
   {
      Event event;
      while (window.pollEvent(event))
      {
         if (event.type == Event::Closed)
            window.close();
      }
      window.clear(Color::White);
      Vertex Axis[] =
      {
         Vertex(Vector2f(50,50)),
         Vertex(Vector2f(50,ywidth - 50)),
         Vertex(Vector2f(xwidth - 50,ywidth - 50))
      };
      for (int i = 0; i < 3; i++)
      {
         Axis[i].color = Color::Black;
      }
      window.draw(Axis, 3, LinesStrip);
      Text textx;
      textx.setFont(font);
      textx.setString("X");
      textx.setFillColor(Color::Black);
      textx.setCharacterSize(18);
      textx.move(Vector2f(xwidth - 25, ywidth - 50));
      window.draw(textx);
      Text texty;
      texty.setFont(font);
      texty.setString("Y");
      texty.setFillColor(Color::Black);
      texty.setCharacterSize(18);
      texty.move(Vector2f(43, 25));
      window.draw(texty);
      if (n <= 15)
      {
         for (int i = 0; i < n; i++)
         {
            Vertex line[] =
            {
               Vertex(Vector2f(50 + (xwidth - 100) * (grid[i] - grid[0]) / (grid[n - 1] - grid[0]),ywidth - 45)),
               Vertex(Vector2f(50 + (xwidth - 100) * (grid[i] - grid[0]) / (grid[n - 1] - grid[0]),ywidth - 55))
            };
            line[0].color = Color::Black;
            line[1].color = Color::Black;
            window.draw(line, 2, Lines);
            Text text;
            text.setFont(font);
            std::ostringstream oss;
            oss << grid[i];
            text.setString(oss.str());
            text.setFillColor(Color::Black);
            text.setCharacterSize(18);
            text.move(Vector2f(50 + (xwidth - 100) * (grid[i] - grid[0]) / (grid[n - 1] - grid[0]) - 9, ywidth - 40));
            window.draw(text);
         }
      }
      else
      {
         for (int i = 0; i < 11; i++)
         {
            Vertex line[] =
            {
               Vertex(Vector2f(50 + (xwidth - 100) * i / 10,ywidth - 45)),
               Vertex(Vector2f(50 + (xwidth - 100) * i / 10,ywidth - 55))
            };
            line[0].color = Color::Black;
            line[1].color = Color::Black;
            window.draw(line, 2, Lines);
            Text text;
            text.setFont(font);
            std::ostringstream oss;
            oss << i * (grid[n - 1] - grid[0]) / 10;
            text.setString(oss.str());
            text.setFillColor(Color::Black);
            text.setCharacterSize(18);
            text.move(Vector2f(50 + (xwidth - 100) * i / 10 - 9, ywidth - 40));
            window.draw(text);
         }
      }
      for (int i = 0; i < 11; i++)
      {
         Vertex line[] =
         {
            Vertex(Vector2f(45,ywidth - 50 - i * 40)),
            Vertex(Vector2f(55,ywidth - 50 - i * 40))
         };
         line[0].color = Color::Black;
         line[1].color = Color::Black;
         window.draw(line, 2, Lines);
         Text text;
         text.setFont(font);
         std::ostringstream oss;
         oss << minf + i * (maxf - minf) / 10;
         text.setString(oss.str());
         text.setFillColor(Color::Black);
         text.setCharacterSize(15);
         text.move(Vector2f(5, ywidth - 60 - i * (ywidth - 100)/10));
         window.draw(text);
      }
      Vertex* plottrue = new Vertex[plotparameter];
      real h = (grid[n - 1] - grid[0]) / (plotparameter - 1);
      real curx = grid[0];
      for (int i = 0; i < plotparameter; i++)
      {
         plottrue[i] = Vertex(Vector2f(50 + (xwidth - 100) * (curx - grid[0]) / (grid[n - 1] - grid[0]), (ywidth - 50) - (ywidth - 100) * (func(curx) - minf) / (maxf - minf)));
         curx += h;
         plottrue[i].color = Color::Blue;
      }
      window.draw(plottrue, plotparameter, LinesStrip);

      Vertex* plotsplain = new Vertex[plotparameter];
      curx = grid[0];
      for (int i = 0; i < plotparameter; i++)
      {
         plotsplain[i] = Vertex(Vector2f(50 + (xwidth - 100) * (curx - grid[0]) / (grid[n - 1] - grid[0]), (ywidth - 50) - (ywidth - 100) * (getsollutionISplain(curx, n, grid, q) - minf) / (maxf - minf)));
         curx += h;
         plotsplain[i].color = Color::Red;
      }
      for (int i = 0; i < n; i++)
      {
         CircleShape point = CircleShape(2);
         point.setFillColor(Color::Black);
         point.move(Vector2f(50 - 2 + (xwidth - 100) * (grid[i] - grid[0]) / (grid[n - 1] - grid[0]), (ywidth - 50) - 2 - (ywidth - 100) * (getsollutionISplain(grid[i], n, grid, q) - minf) / (maxf - minf)));
         window.draw(point);
      }
      for (int i = 0; i < m; i++)
      {
         CircleShape point = CircleShape(1);
         point.setFillColor(Color::Magenta);
         point.move(Vector2f(50 - 1 + (xwidth - 100) * (x[i] - grid[0]) / (grid[n - 1] - grid[0]), (ywidth - 50) - 1 - (ywidth - 100) * (y[i] - minf) / (maxf - minf)));
         window.draw(point);
      }
      window.draw(plotsplain, plotparameter, LinesStrip);
      window.display();
   }
}

void ISplain(real* grid, real* f, real* q, int n)
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

void SSplain(real* grid, real* q, int n, real* x, real* y, int pcount, real alpha, real betta)
{
   int* ia = new int[2 * n + 1];
   real* di = new real[2 * n];
   ia[0] = 0;
   ia[1] = 0;
   ia[2] = 1;
   for (int i = 2; i < 2 * n; i += 2)
   {
      ia[i + 1] = ia[i] + 2;
      ia[i + 2] = ia[i] + 5;
   }
   real* al = new real[ia[2 * n]];
   int* ja = new int[ia[2 * n]];
   real* b = new real[2 * n];
   for (int i = 0; i < 2 * n; i++)
   {
      di[i] = 0;
      b[i] = 0;
      q[i] = 0;
   }
   ja[0] = 0;
   for (int i = 1; i < ia[2 * n]; i += 5)
   {
      ja[i] = 2 * (i - 1) / 5;
      ja[i + 1] = 2 * (i - 1) / 5 + 1;
      ja[i + 2] = 2 * (i - 1) / 5;
      ja[i + 3] = 2 * (i - 1) / 5 + 1;
      ja[i + 4] = 2 * (i - 1) / 5 + 2;
   }
   for (int i = 0; i < ia[2 * n]; i++)
   {
      al[i] = 0;
   }

   for (int i = 0; i < pcount; i++)
   {
      if (x[i] <= grid[n - 1] && x[i] >= grid[0])
      {
         int left = 0;
         int right = n - 1;
         int cur = n / 2;
         while (right - left > 1)
         {
            if (x[i] > grid[cur])
               left = cur;
            else
               right = cur;
            cur = (left + right) / 2;
         }
         real h = (grid[right] - grid[left]);
         real t = (x[i] - grid[left]) / h;
         real p1 = psi1(t);
         real p2 = h * psi2(t);
         real p3 = psi3(t);
         real p4 = h * psi4(t);
         di[2 * left] += p1 * p1;
         di[2 * left + 1] += p2 * p2;
         di[2 * right] += p3 * p3;
         di[2 * right + 1] += p4 * p4;

         al[ia[2 * left + 2] - 1] += p1 * p2;
         al[ia[2 * right]] += p1 * p3;
         al[ia[2 * right] + 1] += p2 * p3;
         al[ia[2 * right + 1]] += p1 * p4;
         al[ia[2 * right + 1] + 1] += p2 * p4;
         al[ia[2 * right + 1] + 2] += p3 * p4;

         b[2 * left] += p1 * y[i];
         b[2 * left + 1] += p2 * y[i];
         b[2 * right] += p3 * y[i];
         b[2 * right + 1] += p4 * y[i];
      }
   }

   for (int i = 0; i < n - 1; i++)
   {
      real h = grid[i + 1] - grid[i];
      di[2 * i] += alpha * 1.2 / h;
      di[2 * i + 1] += alpha * 4.0 / h / 30;
      di[2 * i + 2] += alpha * 1.2 / h;
      di[2 * i + 3] += alpha * 4.0 / h / 30;
      al[ia[2 * i + 2] - 1] += alpha * 0.1 / h;
      al[ia[2 * i + 2]] += alpha * (-1.2) / h;
      al[ia[2 * i + 2] + 1] += alpha * -0.1 / h;
      al[ia[2 * i + 3]] += alpha * 0.1 / h;
      al[ia[2 * i + 3] + 1] += alpha / -h / 30;
      al[ia[2 * i + 3] + 2] += alpha * -0.1 / h;

      di[2 * i] += betta * 12.0 / (h * h * h);
      di[2 * i + 1] += betta * 4.0 / (h);
      di[2 * i + 2] += betta * 12.0 / (h * h * h);
      di[2 * i + 3] += betta * 4.0 / (h);
      al[ia[2 * i + 2] - 1] += betta * 6.0 / (h * h);
      al[ia[2 * i + 2]] += betta * (-12.0) / (h * h * h);
      al[ia[2 * i + 2] + 1] += betta * (-6.0) / (h * h);
      al[ia[2 * i + 3]] += betta * 6.0 / (h * h);
      al[ia[2 * i + 3] + 1] += betta * 2.0 / (h);
      al[ia[2 * i + 3] + 2] += betta * (-6.0) / (h * h);
   }
   MSG(ia, ja, 2 * n, al, di, q, b, 100000, 1e-15);
}


real getsollutionISplain(real x, int n, real* grid, real* q)
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
   return  x * sinf(x) + 2 * x;
}



real psi1(real t)
{
   return 2 * (t + 0.5) * (t - 1) * (t - 1);
}
real psi2(real t)
{
   return t * (t - 1) * (t - 1);
}

real psi3(real t)
{
   return (-2) * t * t * (t - 1.5);
}

real psi4(real t)
{
   return  t * t * (t - 1);
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
      betta *= DotProduct(r, r, n);
      for (int i = 0; i < n; i++)
      {
         p[i] = r[i] + betta * p[i];
      }
      k++;
   }
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
      for (int k = ia[i]; k < ia[i + 1]; k++)
      {
         int j = ja[k];
         b[i] += al[k] * x[j];
         b[j] += al[k] * x[i];
      }
   }
}