#include "Matrix4.h"

#include <cmath>

Vector4 Matrix4::operator*(const Vector4 &vec) const {
  return Vector4{vec.x * a.x + vec.y * b.x + vec.z * c.x + vec.w * d.x,
                 vec.x * a.y + vec.y * b.y + vec.z * c.y + vec.w * d.y,
                 vec.x * a.z + vec.y * b.z + vec.z * c.z + vec.w * d.z,
                 vec.x * a.w + vec.y * b.w + vec.z * c.w + vec.w * d.w};
}

Matrix4 Matrix4::operator*(const Matrix4 &other) const {
  return Matrix4{(*this) * other.a, (*this) * other.b, (*this) * other.c,
                 (*this) * other.d};
}

Matrix4::Matrix4(const Vector4 &vec1, const Vector4 &vec2, const Vector4 &vec3,
                 const Vector4 &vec4)
    : a(vec1), b(vec2), c(vec3), d(vec4) {}

Matrix4 Matrix4::GetTranspose() const {
  return Matrix4{Vector4{a.x, b.x, c.x, d.x}, Vector4{a.y, b.y, c.y, d.y},
                 Vector4{a.z, b.z, c.z, d.z}, Vector4{a.w, b.w, c.w, d.w}};
}

Matrix4 Matrix4::RotateX(float phi) {
  auto cos_phi = std::cos(phi);
  auto sin_phi = std::sin(phi);
  return Matrix4{Vector4{1, 0, 0, 0}, Vector4{0, cos_phi, sin_phi, 0},
                 Vector4{0, -sin_phi, cos_phi, 0}, Vector4{0, 0, 0, 1}};
}

Matrix4 Matrix4::RotateY(float phi) {
  auto cos_phi = std::cos(phi);
  auto sin_phi = std::sin(phi);
  return Matrix4{Vector4{cos_phi, 0, -sin_phi, 0}, Vector4{0, 1, 0, 0},
                 Vector4{sin_phi, 0, cos_phi, 0}, Vector4{0, 0, 0, 1}};
}

Matrix4 Matrix4::RotateZ(float phi) {
  auto cos_phi = std::cos(phi);
  auto sin_phi = std::sin(phi);
  return Matrix4{Vector4{cos_phi, sin_phi, 0, 0},
                 Vector4{-sin_phi, cos_phi, 0, 0}, Vector4{0, 0, 1, 0},
                 Vector4{0, 0, 0, 1}};
}

Matrix4 Matrix4::Translate(Vector const &dispacepent) {
  return Matrix4{Vector4{1, 0, 0, 0}, Vector4{0, 1, 0, 0}, Vector4{0, 0, 1, 0},
                 Vector4{dispacepent, 1}};
}

Matrix4 Matrix4::Scale(float scalar) {
  return Matrix4{Vector4{scalar, 0, 0, 0}, Vector4{0, scalar, 0, 0},
                 Vector4{0, 0, scalar, 0}, Vector4{0, 0, 0, 1}};
}

Matrix4 Matrix4::ScaleX(float scalar) {
  return Matrix4{Vector4{scalar, 0, 0, 0}, Vector4{0, 1, 0, 0},
                 Vector4{0, 0, 1, 0}, Vector4{0, 0, 0, 1}};
}

Matrix4 Matrix4::ScaleY(float scalar) {
  return Matrix4{Vector4{1, 0, 0, 0}, Vector4{0, scalar, 0, 0},
                 Vector4{0, 0, 1, 0}, Vector4{0, 0, 0, 1}};
}

Matrix4 Matrix4::ScaleZ(float scalar) {
  return Matrix4{Vector4{1, 0, 0, 0}, Vector4{0, 1, 0, 0},
                 Vector4{0, 0, scalar, 0}, Vector4{0, 0, 0, 1}};
}
