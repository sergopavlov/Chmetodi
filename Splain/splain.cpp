#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Splain.h"
#include <cmath>
#include <string>
#include <sstream>


using namespace sf;

int main()
{
   int n = 5;
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
   real minf = f[0], maxf = f[0];
   for (int i = 1; i < n; i++)
   {
      if (f[i] > maxf)
         maxf = f[i];
      if (f[i] < minf)
         minf = f[i];
   }
   Font font;
   font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
   int plotparameter = 100;
   ContextSettings settings;
   settings.antialiasingLevel = 2;
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
      Text x;
      x.setFont(font);
      x.setString("X");
      x.setFillColor(Color::Black);
      x.setCharacterSize(18);
      x.move(Vector2f(725, 440));
      window.draw(x);
      Text y;
      y.setFont(font);
      y.setString("Y");
      y.setFillColor(Color::Black);
      y.setCharacterSize(18);
      y.move(Vector2f(43, 25));
      window.draw(y);
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
      real h = (grid[n - 1] - grid[0])/(plotparameter-1);
      real curx = grid[0];
      for (int i = 0; i < plotparameter; i++)
      {
         plottrue[i] = Vertex(Vector2f(50 + 650*(curx - grid[0]) / (grid[n - 1] - grid[0]), 450 - 400 * (func(curx) - minf) / (maxf - minf)));
         curx += h;
         plottrue[i].color = Color::Blue;
      }
      window.draw(plottrue, plotparameter, LinesStrip);

      Vertex* plotsplain = new Vertex[plotparameter];
      curx = grid[0];
      for (int i = 0; i < plotparameter; i++)
      {
         plotsplain[i] = Vertex(Vector2f(50 + 650 * (curx - grid[0]) / (grid[n - 1] - grid[0]), 450 - 400 * (getsollution(curx,n,grid,q) - minf) / (maxf - minf)));
         curx += h;
         plotsplain[i].color = Color::Red;
      }
      window.draw(plotsplain, plotparameter, LinesStrip);


      window.display();



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