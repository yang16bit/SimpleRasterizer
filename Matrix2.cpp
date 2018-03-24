#include "Matrix2.h"

Matrix2 Matrix2::operator*(const Matrix2 &m) const {
  return Matrix2{(*this) * m.vecs[0], (*this) * m.vecs[1]};
}

void Matrix2::operator*=(const Matrix2 &m) { *this = (*this) * m; }

Vector2 Matrix2::operator*(const Vector2 &v) const {
  return Vector2{v.x * a + v.y * c, v.x * b + v.y * d};
}

float Matrix2::GetDet() const {
  auto &a = this->vecs[0];
  auto &b = this->vecs[1];
  return a.x * b.y - b.x * a.y;
}

Vector2 Matrix2::SolveLinearEquasSys(const Vector2 &v) const {
  auto det = this->GetDet();
  return Vector2{Matrix2{v, v2}.GetDet() / det, Matrix2{v1, v}.GetDet() / det};
}

bool Matrix2::operator==(const Matrix2 &A) { return v1 == A.v1 && v2 == A.v2; }

Matrix2::Matrix2(const Vector2 &a, const Vector2 &b) : v1(a), v2(b) {}
