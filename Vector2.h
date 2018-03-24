#ifndef CH4_VECTOR2_HPP
#define CH4_VECTOR2_HPP

#include <cstdint>

struct Vector2 {
  float x, y;

  // 0 for x, 1 for y, 2 for z
  float &Componant(size_t index);

  Vector2 operator+(const Vector2 &) const;
  void operator+=(const Vector2 &);
  Vector2 operator-(const Vector2 &) const;
  void operator-=(const Vector2 &);
  Vector2 operator*(const float scalar) const;
  void operator*=(const float scalar);
  float AnalogCross(const Vector2 &) const;
  float Dot(const Vector2 &) const;
  bool operator==(const Vector2 &v) const;
  bool operator!=(const Vector2 &v) const;
  void Normalize();
  Vector2 GetNormal() const;
  float GetLength() const;
};

#endif // CH4_VECTOR2_HPP
