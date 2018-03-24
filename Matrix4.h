#ifndef CH8_MATRIX4_H
#define CH8_MATRIX4_H

#include "Vector4.h"

struct Matrix4 {
  union {
    Vector4 vecs[4];
    struct {
      float a1, a2, a3, a4, // vecs[0]
          b1, b2, b3, b4,   // vecs[1]
          c1, c2, c3, c4,   // vecs[2]
          d1, d2, d3, d4;   // vecs[3]
    };
    struct {
      Vector4 v1, v2, v3, v4;
    };
    struct {
      Vector4 a, b, c, d;
    };
  };

  Matrix4(const Vector4 &vec1 = Vector4{1, 0, 0, 0},
          const Vector4 &vec2 = Vector4{0, 1, 0, 0},
          const Vector4 &vec3 = Vector4{0, 0, 1, 0},
          const Vector4 &vec4 = Vector4{0, 0, 0, 1});

  Vector4 operator*(const Vector4 &other) const;
  Matrix4 operator*(const Matrix4 &other) const;
  Matrix4 GetTranspose() const;

  // construct transforms
  static Matrix4 RotateX(float radian);
  static Matrix4 RotateY(float radian);
  static Matrix4 RotateZ(float radian);
  static Matrix4 Translate(Vector const &dispacepent);
  static Matrix4 Scale(float scalar);
  static Matrix4 ScaleX(float scalar);
  static Matrix4 ScaleY(float scalar);
  static Matrix4 ScaleZ(float scalar);
};

#endif // CH8_MATRIX4_H
