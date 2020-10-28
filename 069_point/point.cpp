#include <cmath>
#include "point.hpp"

double Point::distanceFrom(const Point & p){
  return std::sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
}
