#include "Vector2.h"
#include <cmath>

float &Vector2::Componant(size_t index) {
  if (index >= 2)
    index %= 2;
  switch (index) {
  case 0:
    return x;
  default: // case 1:
    return y;
  }
}

Vector2 Vector2::operator+(const Vector2 &a) const {
  return Vector2{x + a.x, y + a.y};
}

void Vector2::operator+=(const Vector2 &v) {
  x += v.x;
  y += v.y;
}

Vector2 Vector2::operator-(const Vector2 &a) const {
  return Vector2{x - a.x, y - a.y};
}

void Vector2::operator-=(const Vector2 &v) {
  x -= v.x;
  y -= v.y;
}

Vector2 Vector2::operator*(const float scalar) const {
  return Vector2{x * scalar, y * scalar};
}

void Vector2::operator*=(const float scalar) {
  x *= scalar;
  y *= scalar;
}

// in 2D space, u.cross(v) is determinant[u,v] or (u.x*v.y-u.y*v.x)
float Vector2::AnalogCross(const Vector2 &v) const {
  auto &u = *this;
  return u.x * v.y - u.y * v.x;
}

float Vector2::Dot(const Vector2 &b) const { return x * b.x + y * b.y; }

bool Vector2::operator==(const Vector2 &v) const {
  return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2 &v) const { return !(*this == v); }

void Vector2::Normalize() { *this = this->GetNormal(); }

Vector2 Vector2::GetNormal() const {
  auto lenth = this->GetLength();
  return Vector2{x / lenth, y / lenth};
}

float Vector2::GetLength() const { return sqrtf(x * x + y * y); }
