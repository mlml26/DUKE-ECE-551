#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
Vector2D Vector2D::operator+(const Vector2D & rhs) const{
  Vector2D answer;
  answer.x = x + rhs.x;
  answer.y = y + rhs.y;
  return answer;
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs){
  x += rhs.x;
  y += rhs.y;
  return *this;
}
double Vector2D::dot(const Vector2D & rhs) const{
  return x * rhs.x + y * rhs.y;
}
void Vector2D::print() const{
  std::printf("%.2f, %.2f", x, y);
}
