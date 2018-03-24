#pragma once
#ifndef CH4_VECTOR_HPP
#define CH4_VECTOR_HPP

#include <cstdint>

struct Vector {
  union {
    struct {
      float x, y, z;
    };
    float Component[3];
  };
  Vector(const float a, const float b, const float c);
  Vector();

  Vector operator+(const Vector &) const;
  void operator+=(const Vector &);
  Vector operator-(const Vector &) const;
  void operator-=(const Vector &);
  Vector operator*(const float scalar) const;
  void operator*=(const float scalar);
  Vector Cross(const Vector &) const;
  float Dot(const Vector &) const;
  bool operator==(const Vector &v) const;
  bool operator!=(const Vector &v) const;
  Vector operator-() const;

  void Normalize();
  Vector GetNormal() const;
  float GetLength() const;
};

class NormalVec : public Vector {
public:
  NormalVec(const Vector &vec);
};

#endif // CH4_VECTOR_HPP
