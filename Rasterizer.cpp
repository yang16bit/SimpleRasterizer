#include "Rasterizer.h"

#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <cassert>
#include <chrono>
#include <limits>
#include <string>
#include <thread>

Rasterizer::Rasterizer()
    : CanvasWindow(600, 500), camera(Vector{8, 4, 0}, Vector{0, 0, 0},
                                     static_cast<float>(canvas.width) /
                                         static_cast<float>(canvas.height)),
      depth_buffer(canvas.width, canvas.height), wire_mode(false),
      speed_scalar(1.f),

      speed_up([&]() mutable { speed_scalar += .2f; }),
      speed_down([&]() mutable { speed_scalar -= .2f; }) {
  this->SetTitle(L"Rasterizer");

  this->keydown_callbacks.insert(
      std::make_pair(KC_SPACE, [this] { this->wire_mode = !this->wire_mode; }));
  this->keydown_callbacks.insert(std::make_pair(KC_UP, speed_up));
  this->keydown_callbacks.insert(std::make_pair(KC_RIGHT, speed_up));
  this->keydown_callbacks.insert(std::make_pair(KC_DOWN, speed_down));
  this->keydown_callbacks.insert(std::make_pair(KC_LEFT, speed_down));
}

void Rasterizer::Start() {
  Window::idleMode = false;
  while (Window::HasUnclosed()) {
    // fps control
    {
      using namespace std::chrono_literals;
      const auto frame_time = 16.6666667ms; // 60fps

      static auto start = std::chrono::high_resolution_clock::now();

      auto mid_rest = std::chrono::high_resolution_clock::now();
      std::chrono::duration<float, std::milli> elapsed = mid_rest - start;
      std::this_thread::sleep_for(frame_time - elapsed);

      auto end = std::chrono::high_resolution_clock::now();
      elapsed = end - start;
      this->SetTitle(
          std::to_wstring(static_cast<unsigned>(1000.f / elapsed.count()))
              .c_str());
      start = end;
    }

    this->canvas.Clear();
    this->PaintCanvas();
    this->Update();
  }
}

void Rasterizer::PaintCanvas() {
  static auto M = [this] {
    auto Mvp = canvas.GetMvp();
    // auto Morth = camera.GetMorth();
    auto Mper = camera.GetMper();
    auto Mcam = camera.GetMcam();
    return Mvp * (Mper * Mcam);
  }();

  auto cube_copy = cube;
  cube_copy.rotation_angleY *= speed_scalar;
  auto Mmodel = cube_copy.GetModelTransform();
  auto Moverall = M * Mmodel;

  cube_copy.ApplyTransform(Moverall);
  if (wire_mode) {
    cube_copy.for_each_edge([&, this](Vector const &p0, Vector const &p1,
                                      Color const &, Color const &) {
      // todo: add clipping to avoid out of canvas range
      canvas.DrawLine(Vector2{p0.x, p0.y}, Vector2{p1.x, p1.y});
    });
  } else {
    depth_buffer.Reset();
    cube_copy.for_each_trig([&, this](Vector const &p1, Vector const &p2,
                                      Vector const &p3, Color const &p1_col,
                                      Color const &p2_col,
                                      Color const &p3_col) {
      // backface culling
      {
        auto edge1 = p2 - p1;
        auto edge2 = p3 - p1;
        auto cross_z = edge1.x * edge2.y - edge2.x * edge1.y;
        if (cross_z < 0)
          return;
      }
      canvas.DrawTriangle(
          Vector2{p1.x, p1.y}, Vector2{p2.x, p2.y}, Vector2{p3.x, p3.y},
          [&, this](Image::Pixel &pixel, size_t x, size_t y, float alpha,
                    float beta, float gama) {
            auto pixel_z = p1.z * alpha + p2.z * beta + p3.z * gama;
            auto &depth = depth_buffer.At(x, y);
            if (depth < pixel_z) {
              pixel = p1_col * alpha + p2_col * beta + p3_col * gama;
              depth = pixel_z;
            }
          });
    });
  }
}

Matrix4 Camera::GetMorth() {
  auto &l = left_plane;
  auto &r = right_plane;
  auto &b = bottom_plane;
  auto &t = top_plane;
  auto &n = near_plane;
  auto &f = far_plane;
  return Matrix4{
      Vector4{2.f / (r - l), 0, 0, 0}, Vector4{0, 2.f / (t - b), 0, 0},
      Vector4{0, 0, 2.f / (n - f), 0},
      Vector4{-(r + l) / (r - l), -(t + b) / (t - b), -(n + f) / (n - f), 1}};
}

Matrix4 Camera::GetMcam() {
  Matrix4 reverse_displacement;
  reverse_displacement.v4 = Vector4{-e, 1};
  Matrix4 reverse_bases =
      Matrix4{Vector4{u, 0}, Vector4{v, 0}, Vector4{w, 0}, Vector4{0, 0, 0, 1}}
          .GetTranspose();

  return reverse_bases * reverse_displacement;
}

Camera::Camera(const Vector &eye, const Vector &look_at, float wh_ratio,
               float VFoV)
    : e(eye), g(look_at - eye), t(Vector{0, 1, 0}) {
  { // order matters
    w = (-g.GetNormal());
    u = t.Cross(w).GetNormal();
    v = w.Cross(u);
  }

  { // planes
    left_plane = -VFoV * wh_ratio / 2;
    right_plane = -left_plane;
    bottom_plane = -VFoV / 2;
    top_plane = -bottom_plane;
    near_plane = 10.f;
    far_plane = -1000.f; // -inf
  }
}

Matrix4 Camera::GetMper() {
  auto n = -near_plane;
  auto f = -far_plane;
  auto perspective =
      Matrix4{Vector4{n, 0, 0, 0}, Vector4{0, n, 0, 0}, Vector4{0, 0, n + f, 1},
              Vector4{0, 0, -(f * n), 0}};
  auto orthogonal = this->GetMorth();
  return orthogonal * perspective;
}

DepthBuffer::DepthBuffer(size_t w, size_t h)
    : data(nullptr), width(w), height(h) {
  data = (float *)std::malloc(width * height * sizeof(float));
  assert(data != nullptr);
}

DepthBuffer::~DepthBuffer() { free(data); }

float &DepthBuffer::At(size_t x, size_t y) {
  return data[y * (width) + // skip rows
              x];
}

void DepthBuffer::Reset() {
  for (float *p = data, *end = (data + width * height); p < end; p++) {
    *p = -(std::numeric_limits<float>::infinity());
  }
}

Rasterizer::Cube::Cube() {
  // init points
  {
    auto o = Vector{0, 0, 0};
    auto x_hat = Vector{1, 0, 0};
    auto y_hat = Vector{0, 1, 0};
    auto z_hat = Vector{0, 0, 1};
    points[1 - 1] = o;
    points[2 - 1] = o + x_hat;
    points[3 - 1] = o + x_hat + z_hat;
    points[4 - 1] = o + z_hat;
    points[5 - 1] = points[1 - 1] + y_hat;
    points[6 - 1] = points[2 - 1] + y_hat;
    points[7 - 1] = points[3 - 1] + y_hat;
    points[8 - 1] = points[4 - 1] + y_hat;
  }

  // init colors
  {
    // generate colors for color cube
    auto make_color = [](const Vector &pt) -> Color {
      return Color{static_cast<uint8_t>(pt.x * 255.f),
                   static_cast<uint8_t>(pt.y * 255.f),
                   static_cast<uint8_t>(pt.z * 255.f)};
    };
    using namespace std;
    assert(sizeof(points) / sizeof(points[0]) == 8);
    assert(sizeof(colors) / sizeof(colors[0]) == 8);
    for (size_t i = 0; i < 8; i++) {
      colors[i] = make_color(points[i]);
    }
  }

  position = Vector{-.5f, -.5f, -.5f};
  rotation_angleY = 1.f;
}

void Rasterizer::Cube::ApplyTransform(Matrix4 const &transform) {
  for (auto &pt : points) {
    pt = (transform * Vector4{pt, 1}).GetCartesian();
  }
}

Rasterizer::Cube::Cube(const Rasterizer::Cube &other)
    : rotation_angleY(other.rotation_angleY), position(other.position) {
  for (size_t i = 0; i < 8; i++) {
    points[i] = other.points[i];
  }
  for (size_t i = 0; i < 8; i++) {
    colors[i] = other.colors[i];
  }
}

Matrix4 Rasterizer::Cube::GetModelTransform() {
  static Matrix4 Mlocal = Matrix4::Translate(position);
  // time elapsed
  static auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> elapsed = end - start;
  start = end;

  auto rotation_y = Matrix4::RotateY(rotation_angleY * elapsed.count());
  Mlocal = rotation_y * Mlocal;
  return Mlocal;
}

void Rasterizer::Cube::for_each_trig(
    std::function<void(Vector const &a, Vector const &b, Vector const &c,
                       Color const &a_col, Color const &b_col,
                       Color const &c_col)>
        action) {
  action(points[2], points[6], points[3], colors[2], colors[6],
         colors[3]); // near face
  action(points[3], points[6], points[7], colors[3], colors[6],
         colors[7]); // near face
  action(points[1], points[5], points[6], colors[1], colors[5],
         colors[6]); // right face
  action(points[1], points[6], points[2], colors[1], colors[6],
         colors[2]); // right face
  action(points[5], points[7], points[6], colors[5], colors[7],
         colors[6]); // top face
  action(points[4], points[7], points[5], colors[4], colors[7],
         colors[5]); // top face
  action(points[0], points[5], points[1], colors[0], colors[5],
         colors[1]); // far face
  action(points[0], points[4], points[5], colors[0], colors[4],
         colors[5]); // far face
  action(points[0], points[7], points[4], colors[0], colors[7],
         colors[4]); // left face
  action(points[3], points[7], points[0], colors[3], colors[7],
         colors[0]); // left face
  action(points[3], points[1], points[2], colors[3], colors[1],
         colors[2]); // bottom face
  action(points[0], points[1], points[3], colors[0], colors[1],
         colors[3]); // bottom face
}

void Rasterizer::Cube::for_each_edge(
    std::function<void(Vector const &a, Vector const &b, Color const &a_col,
                       Color const &b_col)>
        action) {
  static const size_t bottom_face_vertices_index[5] = {0, 1, 2, 3, 0};
  for (size_t i = 0; i <= 3; i++) {
    auto idx_btm = bottom_face_vertices_index[i];
    auto idx_btm_next = bottom_face_vertices_index[i + 1];
    auto idx_top = idx_btm + 4;
    auto idx_top_next = idx_btm_next + 4;
    // bottom face edges
    action(points[idx_btm], points[idx_btm_next], colors[idx_btm],
           colors[idx_btm_next]);
    // pillars
    action(points[idx_btm], points[idx_top], colors[idx_btm], colors[idx_top]);
    // top face edges
    action(points[idx_top], points[idx_top_next], colors[idx_top],
           colors[idx_top_next]);
  }
}
