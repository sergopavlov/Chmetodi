#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Splain.h"
#include <math.h>
#include <string>
#include <sstream>
#include "SolveSLAE.h"

# define M_PI           3.14159265358979323846
using namespace sf;

int main()
{
   int n = 16;
   int m = 5 * (n - 1) + 1;
   real* x = new real[m];
   real* y = new real[m];
   real* grid = new real[n];
   real h = 0.5;
   for (int i = 0; i < n; i++)
   {
      grid[i] = i * h;
   }
   for (int i = 0; i < m; i++)
   {
      x[i] = i * h / 5;
   }
   getfuncarray(m, y, x);
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
   SSplain(grid, q, n, x, y, m, 1e-1, 1e-1);
   //ISplain(grid, f, q, n);
   Font font;
   font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
   int plotparameter = 500;
   ContextSettings settings;
   settings.antialiasingLevel = 7;
   RenderWindow window(VideoMode(750, 500), "Splain!", Style::Default, settings);
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
         Vertex(Vector2f(50,450)),
         Vertex(Vector2f(700,450))
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
      textx.move(Vector2f(725, 440));
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
               Vertex(Vector2f(50 + 650 * (grid[i] - grid[0]) / (grid[n - 1] - grid[0]),455)),
               Vertex(Vector2f(50 + 650 * (grid[i] - grid[0]) / (grid[n - 1] - grid[0]),445))
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
            text.move(Vector2f(50 + 650 * (grid[i] - grid[0]) / (grid[n - 1] - grid[0]) - 9, 460));
            window.draw(text);
         }
      }
      else
      {
         for (int i = 0; i < 11; i++)
         {
            Vertex line[] =
            {
               Vertex(Vector2f(50 + 650 * i / 10,455)),
               Vertex(Vector2f(50 + 650 * i / 10,445))
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
            text.move(Vector2f(50 + 650 * i / 10 - 9, 460));
            window.draw(text);
         }
      }
      for (int i = 0; i < 11; i++)
      {
         Vertex line[] =
         {
            Vertex(Vector2f(45,450 - i * 40)),
            Vertex(Vector2f(55,450 - i * 40))
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
         text.move(Vector2f(5, 440 - i * 40));
         window.draw(text);
      }
      Vertex* plottrue = new Vertex[plotparameter];
      real h = (grid[n - 1] - grid[0]) / (plotparameter - 1);
      real curx = grid[0];
      for (int i = 0; i < plotparameter; i++)
      {
         plottrue[i] = Vertex(Vector2f(50 + 650 * (curx - grid[0]) / (grid[n - 1] - grid[0]), 450 - 400 * (func(curx) - minf) / (maxf - minf)));
         curx += h;
         plottrue[i].color = Color::Blue;
      }
      window.draw(plottrue, plotparameter, LinesStrip);

      Vertex* plotsplain = new Vertex[plotparameter];
      curx = grid[0];
      for (int i = 0; i < plotparameter; i++)
      {
         plotsplain[i] = Vertex(Vector2f(50 + 650 * (curx - grid[0]) / (grid[n - 1] - grid[0]), 450 - 400 * (getsollutionISplain(curx, n, grid, q) - minf) / (maxf - minf)));
         curx += h;
         plotsplain[i].color = Color::Red;
      }
      for (int i = 0; i < n; i++)
      {
         CircleShape point = CircleShape(2);
         point.setFillColor(Color::Black);
         point.move(Vector2f(50 - 2 + 650 * (grid[i] - grid[0]) / (grid[n - 1] - grid[0]), 450 - 2 - 400 * (getsollutionISplain(grid[i], n, grid, q) - minf) / (maxf - minf)));
         window.draw(point);
      }
      for (int i = 0; i < m; i++)
      {
         CircleShape point = CircleShape(1);
         point.setFillColor(Color::Magenta);
         point.move(Vector2f(50 - 1 + 650 * (x[i] - grid[0]) / (grid[n - 1] - grid[0]), 450 - 1 - 400 * (y[i] - minf) / (maxf - minf)));
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
      q[2 * i + 1] = (f[i + 1] - f[i]);
   }
   q[2 * n - 2] = f[n - 1];
   q[2 * n - 1] = (f[n - 1] - f[n - 2]);
}

void SSplain(real* grid, real* q, int n, real* x, real* y, int pcount, real alpha, real betta)
{
   int* ia = new int[2 * n + 1];
   real* di = new real[2 * n];
   int* d = new int[2 * n];
   ia[0] = 0;
   ia[1] = 0;
   ia[2] = 1;
   for (int i = 2; i < 2 * n; i += 2)
   {
      ia[i + 1] = ia[i] + 2;
      ia[i + 2] = ia[i] + 5;
   }
   real* al = new real[ia[2 * n]];
   real* b = new real[2 * n];
   for (int i = 0; i < 2 * n; i++)
   {
      di[i] = 0;
      d[i] = 0;
      b[i] = 0;
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
         real t = (x[i] - grid[left]) / (grid[right] - grid[left]);
         real p1 = psi1(t);
         real p2 = psi2(t);
         real p3 = psi3(t);
         real p4 = psi4(t);
         di[2 * left] += p1 * p1;
         di[2 * left + 1] += p2 * p2;
         di[2 * right] += p3 * p3;
         di[2 * right + 1] += p4 * p4;
         al[ia[2 * left + 1]] += p1 * p2;
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
      di[2 * i + 1] += alpha * 4.0 * h / 30;
      di[2 * i + 2] += alpha * 1.2 / h;
      di[2 * i + 3] += alpha * 4.0 * h / 30;
      al[ia[2 * i + 1]] += alpha * 0.1;
      al[ia[2 * i + 2]] += alpha * (-1.2) / h;
      al[ia[2 * i + 2] + 1] += alpha * -0.1;
      al[ia[2 * i + 3]] += alpha * 0.1;
      al[ia[2 * i + 3] + 1] += alpha * -h / 30;
      al[ia[2 * i + 3] + 2] += alpha * -0.1;

      di[2 * i] += betta * 12.0 / (h * h * h);
      di[2 * i + 1] += betta * 4.0 / h;
      di[2 * i + 2] += betta * 12.0 / (h * h * h);
      di[2 * i + 3] += betta * 4.0 / h;
      al[ia[2 * i + 1]] += betta * 6.0 / (h * h);
      al[ia[2 * i + 2]] += betta * (-12.0) / (h * h * h);
      al[ia[2 * i + 2] + 1] += betta * (-6.0) / (h * h);
      al[ia[2 * i + 3]] += betta * 6.0 / (h * h);
      al[ia[2 * i + 3] + 1] += betta * 2.0 / h;
      al[ia[2 * i + 3] + 2] += betta * (-6.0) / (h * h);
   }

   
   Solve(al, di, ia, d, 2 * n, b);
   for (int i = 0; i < 2 * n; i++)
   {
      q[i] = b[i];
   }
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
   res += q[2 * left + 1] * t * (t - 1) * (t - 1);
   res += q[2 * right] * (-2) * t * t * (t - 1.5);
   res += q[2 * right + 1] * t * t * (t - 1);
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
   return  x * x;
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