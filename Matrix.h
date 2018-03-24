#pragma once
#ifndef CH4_MATRIX_HPP
#define CH4_MATRIX_HPP

#include "Vector.h"

class Matrix {
public:
  Matrix(const Vector &vec1 = Vector{1, 0, 0},
         const Vector &vec2 = Vector{0, 1, 0},
         const Vector &vec3 = Vector{0, 0, 1});
  //    Matrix(const float &a,const float &b, const float &c, // vec 1
  //           const float &d,const float &e, const float &f, // vec 2
  //           const float &g,const float &h, const float &i  // vec 3
  //    );
  virtual ~Matrix();
  union {
    Vector vecs[3];
    struct {
      float a, b, c, // vecs[0]
          d, e, f,   // vecs[1]
          g, h, i;   // vecs[2]
    };
    struct {
      float a1, a2, a3, // vecs[0]
          b1, b2, b3,   // vecs[1]
          c1, c2, c3;   // vecs[2]
    };
    struct {
      Vector x, y, z;
    };
  };
  float GetDet() const;
  Vector operator*(const Vector &v) const;
  Matrix operator*(const Matrix &A) const;
  void operator*=(const Matrix &A);
  bool operator==(const Matrix &A);

  // [M][x]=[v], function returns [x]
  Vector SolveLinearEquasSys(const Vector &v) const;
};

#endif // CH4_MATRIX_HPP
