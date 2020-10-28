#include "circle.hpp"
#include <cmath>
#include <algorithm>

void Circle::move(double dx, double dy){
  c.move(dx,dy);
}
double Circle::intersectionArea(const Circle & otherCircle){
  double d = c.distanceFrom(otherCircle.c);
  if(d >= (r + otherCircle.r)){
    return 0.0;
  }
  if(d <= abs(r - otherCircle.r)){
    double mini = std::min(r, otherCircle.r);
    return (M_PI * mini * mini);
  }
  double a = r * r;
  double b = otherCircle.r * otherCircle.r;
  double x = (a - b + (d * d)) / (2 * d);
  double z = x * x;
  double y = sqrt(a - z);
  double result = a * asin(y / r) + (b * asin(y / otherCircle.r)) - y * (x + sqrt(z + b - a));
  return result;
}
