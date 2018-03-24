#pragma once
#ifndef CH8_CANVAS_H
#define CH8_CANVAS_H

#include <cstdint>

#include "Matrix4.h"
#include "Vector2.h"
#include <functional>

struct Color {
  uint8_t r, g, b;
  Color operator*(const float k) const;
  Color operator+(const Color &color) const;
  void operator+=(const Color &color);
  bool operator==(const Color &b) const;
};
class Image {
public:
  Image(const unsigned int w, const unsigned int h);
  Image(uint8_t const *const pixels, const unsigned w, const unsigned int h);
  Image(Image &other);
  Image &operator=(const Image &other);
  ~Image();
  unsigned int width;
  unsigned int height;
  struct Pixel {
    uint8_t b, g, r;
    inline void operator=(const Color &color) {
      this->b = color.b;
      this->g = color.g;
      this->r = color.r;
    }
  };
  struct ScanLine {
    void *line_pos;
    inline Pixel &operator[](size_t x_idx) {
      return *reinterpret_cast<Pixel *>(reinterpret_cast<char *>(line_pos) +
                                        sizeof(Pixel) * x_idx);
    }

    inline const Pixel &operator[](size_t x_idx) const {
      return *reinterpret_cast<Pixel *>(reinterpret_cast<char *>(line_pos) +
                                        sizeof(Pixel) * x_idx);
    }
  };
  inline ScanLine operator[](size_t y_idx) {
    return ScanLine{this->data + this->GetRowSize() * y_idx};
  }
  inline const ScanLine operator[](size_t y_idx) const {
    return ScanLine{this->data + this->GetRowSize() * y_idx};
  }
  uint8_t *data;
  size_t scanline_stride;

  size_t GetDataSize() const;
  size_t GetRowSize() const;

  void DrawLine(Vector2 p0, Vector2 p1);
  void DrawTriangle(Vector2 a, Vector2 b, Vector2 c,
                    const Color &a_color = Color{255, 255, 255},
                    const Color &b_color = Color{255, 255, 255},
                    const Color &c_color = Color{255, 255, 255});

  void
  DrawTriangle(Vector2 a, Vector2 b, Vector2 c,
               std::function<void(Pixel &pixel, size_t x, size_t y, float alpha,
                                  float beta, float gama)> const &pixel_shader);

  Pixel &At(unsigned x, unsigned y);
  void for_each_pixel_x_y(
      std::function<void(Pixel &, unsigned x, unsigned y)> const &action);
  void for_each_pixel_range_x_y(
      unsigned l, unsigned r, unsigned b, unsigned t,
      std::function<void(Pixel &, unsigned x, unsigned y)> const &action);
  void Clear();
  // make a copy that scaled up by the factor
  Image operator*(size_t const factor);

  // matrix view port
  Matrix4 GetMvp();

protected:
};

#endif // CH8_CANVAS_H
