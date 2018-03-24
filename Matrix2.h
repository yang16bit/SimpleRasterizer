#ifndef CH4_MATRIX2_HPP
#define CH4_MATRIX2_HPP

#include "Vector2.h"

struct Matrix2 {
  union {
    Vector2 vecs[2]{};
    struct {
      Vector2 v1, v2;
    };
    struct {
      float a, b, c, d;
    };
    struct {
      float a1, a2, b1, b2;
    };
    struct {
      float ax, ay, bx, by;
    };
  };
  Matrix2(const Vector2 &a = Vector2{1, 0}, const Vector2 &b = Vector2{0, 1});
  Matrix2 operator*(const Matrix2 &m) const;
  void operator*=(const Matrix2 &m);
  Vector2 operator*(const Vector2 &v) const;
  bool operator==(const Matrix2 &A);

  float GetDet() const;
  Vector2 SolveLinearEquasSys(const Vector2 &v) const;
};

#endif // CH4_MATRIX2_HPP
