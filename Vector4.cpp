#include "Vector4.h"

Vector4 Vector4::operator+(const Vector4 &other) const {
  return Vector4{x + other.x, y + other.y, z + other.z, w + other.w};
}

void Vector4::operator+=(const Vector4 &other) {
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
}

Vector4 Vector4::operator-(const Vector4 &other) const {
  return Vector4{x - other.x, y - other.y, z - other.z, w - other.w};
}

void Vector4::operator-=(const Vector4 &other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
}

Vector4 Vector4::operator*(const float scalar) const {
  return Vector4{x * scalar, y * scalar, z * scalar, w * scalar};
}

void Vector4::operator*=(const float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;
}

bool Vector4::operator==(const Vector4 &other) const {
  return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vector4::operator!=(const Vector4 &other) const {
  return !((*this) == other);
}

Vector Vector4::GetCartesian() {
  if (w == 0) {
    return Vector{x, y, z};
  } else if (w == 1) {
    return Vector{x, y, z};
  } else {
    return Vector{x /= w, y /= w, z /= w};
  }
}

Vector4::Vector4(const float a, const float b, const float c, const float d)
    : x(a), y(b), z(c), w(d) {}

Vector4::Vector4(const Vector &vec, const float d)
    : x(vec.x), y(vec.y), z(vec.z), w(d) {}
