#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>

double poly(double x) { return pow(x, 3) - x - 2; }

double bissection(std::function<double(double)> f, double a, double b,
                  const double eps = 0.0005, int max_it = 100) {
  assert(f(a) < 0 != f(b) < 0);

  double c = (a + b) / 2.;
  int i = 0;
  while ((b - a) > 2.0 * eps && i < max_it) {
    if (f(c) == 0.0)
      break;

    if (f(a) < 0.0 == f(c) < 0.0)
      a = c;
    else
      b = c;
    c = (a + b) / 2.;
    i++;
  }

  std::cout << "Bissection final iteration " << i << std::endl;
  return c;
}

double false_position(std::function<double(double)> f, double a, double b,
                      const double eps = 0.0005, int max_it = 100) {

  double c;
  int i = 0;
  while ((b - a) / 2.0 > eps && i < max_it) {
    c = (a * f(b) - b * f(a)) / (f(b) - f(a));
    if (f(c) == 0.0)
      break;

    if (f(a) < 0.0 == f(c) < 0.0)
      a = c;
    else
      b = c;
    i++;
  }

  std::cout << "False position  final iteration " << i << std::endl;
  return c;
}

// It gets to the solution faster but way more operation, need to check when the
// tradeoff is worth it.
double itp(std::function<double(double)> f, double a, double b,
           const double eps = 0.0005, int n0 = 1, double k1 = 0.1,
           double k2 = 2., int max_it = 100) {

  int i = 0;
  int n_half = ceil(log2((b - a) / (2 * eps)));
  int n_max = n_half + n0;
  double c, r, delta, c2, xt, x;
  int sigma;

  double fa = f(a), fb = f(b), fx;

  while (b - a > 2 * eps && i < max_it) {
    c = (a + b) / 2.;                              // midpoint
    r = eps * pow(2., n_max - i) - ((b - a) / 2.); // Tolerance
    delta = k1 * pow(b - a, k2);                   // perturbator

    c2 = (a * fb - b * fa) / (fb - fa); // interpolation

    sigma = (c - c2) < 0 ? -1 : 1; // sign for the perturbator

    if (delta <= fabs(c - c2))
      xt = c2 + delta * sigma;
    else
      xt = c;

    if (fabs(xt - c) <= r)
      x = xt;
    else
      x = c - sigma * r; // idk why reducing the tolerance helps here

    fx = f(x);

    if (fx > 0) {
      b = x;
      fb = fx;

    } else if (fx < 0) {
      a = x;
      fa = fx;
    } else {
      a = x;
      b = x;
      break;
    }
    i++;
  }
  std::cout << "ITP final iteration " << i << std::endl;
  return (a + b) / 2.0;
}

int main() {

  double root = bissection(sin, 3, 3.2);

  std::cout << std::setprecision(10) << root << std::endl;

  double root2 = false_position(sin, 3, 3.2);

  std::cout << std::setprecision(10) << root2 << std::endl;

  double root3 = itp(sin, 3, 3.2);

  std::cout << std::setprecision(10) << root3 << std::endl;

  double root_poly = bissection(poly, 1, 2);

  std::cout << std::setprecision(10) << root_poly << std::endl;

  double root2_poly = false_position(poly, 1, 2);

  std::cout << std::setprecision(10) << root2_poly << std::endl;

  double root3_poly = itp(poly, 1, 2);

  std::cout << std::setprecision(10) << root3_poly << std::endl;
  return 0;
}
