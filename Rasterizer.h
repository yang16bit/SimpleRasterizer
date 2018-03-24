#pragma once
#ifndef CH8_RASTERIZER_H
#define CH8_RASTERIZER_H

#include "CanvasWindow.h"

#include "Image.h"
#include "Matrix4.h"
#include "Vector.h"
#include "Vector2.h"

#include <functional>
#include <vector>

struct DepthBuffer {
  explicit DepthBuffer(size_t width, size_t height);
  DepthBuffer(DepthBuffer &) = delete;
  DepthBuffer &operator=(DepthBuffer &) = delete;
  ~DepthBuffer();
  float *data;
  float &At(size_t x, size_t y);
  void Reset();
  size_t width, height;
};

class Camera {
public:
  explicit Camera(const Vector &eye, const Vector &look_at, float wh_ratio,
                  float VFoV = 2.f);

  Matrix4 GetMorth(); // orthogonal transformation
  Matrix4 GetMcam();  // camera transformation
  Matrix4 GetMper();  // perspective transformation

private:
  float left_plane, right_plane, bottom_plane, top_plane, near_plane, far_plane;

  Vector e; // eye
  Vector g; // gaze
  Vector t; // top

  Vector u, v, w;
};

class Rasterizer : public CanvasWindow {
public:
  Rasterizer();
  void Start();

private:
  virtual void PaintCanvas();

  class Cube {
  public:
    explicit Cube();
    Cube(const Cube &other);
    Cube &operator=(Cube &) = delete;
    Vector points[8];
    Color colors[8];
    void ApplyTransform(Matrix4 const &transform);
    Matrix4 GetModelTransform();
    void
    for_each_trig(std::function<void(Vector const &a, Vector const &b,
                                     Vector const &c, Color const &a_col,
                                     Color const &b_col, Color const &c_col)>);
    void
    for_each_edge(std::function<void(Vector const &a, Vector const &b,
                                     Color const &a_col, Color const &b_col)>);

    float rotation_angleY;

  private:
    Vector position;
  };

  const Cube cube;

  Camera camera;
  DepthBuffer depth_buffer;
  bool wire_mode;
  float speed_scalar;
  std::function<void()> speed_up;
  std::function<void()> speed_down;
};

#endif // CH8_RASTERIZER_H
