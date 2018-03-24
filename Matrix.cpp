#include "Matrix.h"

Matrix::Matrix(const Vector &vec1, const Vector &vec2, const Vector &vec3)
    : vecs{vec1, vec2, vec3} {}

Matrix::~Matrix() {}

float Matrix::GetDet() const {
  return a1 * (b2 * c3 - b3 * c2) - a2 * (b1 * c3 - b3 * c1) +
         a3 * (b1 * c2 - b2 * c1);
}

Vector Matrix::operator*(const Vector &v) const {
  return Vector{
      v.x * a + v.y * d + v.z * h, // x
      v.x * b + v.y * e + v.z * g, // y
      v.x * c + v.y * f + v.z * i  // z
  };
}

Matrix Matrix::operator*(const Matrix &A) const {
  return Matrix{
      (*this) * A.vecs[0], // x
      (*this) * A.vecs[1], // y
      (*this) * A.vecs[2]  // z
  };
}

void Matrix::operator*=(const Matrix &A) { *this = (*this) * A; }

bool Matrix::operator==(const Matrix &A) {
  Matrix &B = *this;
  return A.x == B.x && A.y == B.y && A.z == B.z;
}

Vector Matrix::SolveLinearEquasSys(const Vector &v) const {
  // todo mergin case, det == 0
  auto det = this->GetDet();
  return Vector{
      Matrix{v, this->y, this->z}.GetDet() / det,
      Matrix{this->x, v, this->z}.GetDet() / det,
      Matrix{this->x, this->y, v}.GetDet() / det,
  };
}