#include "circle.hpp"
#include <cmath>
#include <algorithm>
#include <cstdio>
void Circle::move(double dx, double dy){
  c.move(dx,dy);
}
double Circle::intersectionArea(const Circle & otherCircle){
  //std::printf("%d",1);
  double d = c.distanceFrom(otherCircle.c);
  if(d > (r + otherCircle.r)){
    return 0.0;
  }
  if(d <= std::abs(r - otherCircle.r)){
    double mini = std::min(r, otherCircle.r);
    return (M_PI * mini * mini);
  }
  
  double a = r * r;
  double b = otherCircle.r * otherCircle.r;
  /*
  double x = (a - b + (d * d)) / (2 * d);
  double z = x * x;
  double y = std::sqrt(a - z);
  double result = a * asin(y / r) + (b * asin(y / otherCircle.r)) - y * (x + std::sqrt(z + b - a));
  return result;
  */
  double a1 = acos((a - b + d * d) / (2 * d * r));
  double a2 = acos((b - a + d * d) / (2 * d * otherCircle.r));
  return a1 * a + a2 * b - d * r * sin(a1);
}
