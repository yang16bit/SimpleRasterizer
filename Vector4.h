#ifndef CH8_VECTOR4_H
#define CH8_VECTOR4_H

#include "Vector.h"
#include <cstdint>

class Vector4 {
public:
  union {
    struct {
      float x, y, z, w;
    };
    float Component[4];
  };

  Vector4(const float a, const float b, const float c, const float d);
  Vector4(const Vector &vec, const float d);

  Vector4 operator+(const Vector4 &) const;
  void operator+=(const Vector4 &);
  Vector4 operator-(const Vector4 &) const;
  void operator-=(const Vector4 &);
  Vector4 operator*(const float scalar) const;
  void operator*=(const float scalar);
  //  Vector4 Cross(const Vector4&) const;
  //  float Dot(const Vector4&) const;
  bool operator==(const Vector4 &v) const;
  bool operator!=(const Vector4 &v) const;
  //  void Normalize();
  //  Vector4 GetNormal() const;
  //  float GetLength() const;
  Vector GetCartesian();
};

#endif // CH8_VECTOR4_H
