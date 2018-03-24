#include "Image.h"
#include "Matrix.h"
#include <cassert>

#include <cmath>
#include <cstring>
#include <limits>

#include <algorithm>

inline std::size_t ALIGN4B(std::size_t bytes) {
  return (((bytes << 3u) + 31u) & ~31u) >> 3u;
}

Image::Image(const unsigned int w, const unsigned int h) : width{w}, height{h} {
  size_t w_bytes_no_pad = w * sizeof(Image::Pixel);
  size_t w_bytes = ALIGN4B(w_bytes_no_pad);
  this->scanline_stride = w_bytes - w_bytes_no_pad;
  size_t bytes = w_bytes * h;
  this->data = (uint8_t *)std::malloc(bytes);
  assert(data != nullptr);
  std::memset(data, 0, bytes);
}

Image::Image(Image &other) : Image(other.width, other.height) {
  memcpy(this->data, other.data, other.GetDataSize());
}

Image::Image(uint8_t const *const pixels, const unsigned w,
             const unsigned int h)
    : Image(w, h) {
  assert(this->scanline_stride == 0);
  memcpy(this->data, pixels, this->GetDataSize());
}

Image &Image::operator=(const Image &other) {
  auto min_width = std::min(this->width, other.width);
  auto min_height = std::min(this->height, other.height);
  for (decltype(min_height) y = 0; y < min_height; y++) {
    for (decltype(min_width) x = 0; x < min_width; x++) {
      (*this)[y][x] = other[y][x];
    }
  }
  return *this;
}

Image::~Image() { std::free(data); }

void Image::DrawLine(Vector2 p0, Vector2 p1) {
  Color line_color{128, 128, 128};

  auto f_x_y = [&p0, &p1](float x, float y) -> float {
    return (p0.y - p1.y) * x + (p1.x - p0.x) * y + p0.x * p1.y - p1.x * p0.y;
  };

  float slope = (p1.y - p0.y) / (p1.x - p0.x);

  // slope ∈ (1,+inf]
  if (slope > 1.f) {
    // make sure p0.y <= p1.y
    if (p0.y > p1.y) {
      std::swap(p0, p1);
    }

    int x = std::round(p0.x);
    int const y1 = std::round(p1.y);

    int y = std::round(p0.y);

    float f_right = f_x_y(static_cast<float>(x) + 0.5f, y + 1);
    float a = (p0.y - p1.y), b = (p1.x - p0.x);

    for (; y <= y1; y++) {
      this->At(x, y) = line_color;

      f_right += b;
      // if (f_x_y( static_cast<float>(x) + 0.5f,y+1) > 0) {
      if (f_right > 0) {
        x++;
        f_right += a;
      }
    }
  }
  // slope ∈ (0,1]
  else if (slope > 0.f) {
    // make sure p0.x <= p1.x
    if (p0.x > p1.x) {
      std::swap(p0, p1);
    }

    int y = std::round(p0.y);
    int const x1 = std::round(p1.x);

    int x = std::round(p0.x);
    float f_down = f_x_y(x + 1, static_cast<float>(y) + 0.5f);
    float a = (p0.y - p1.y), b = (p1.x - p0.x);

    for (; x <= x1; x++) {
      this->At(x, y) = line_color;
      f_down += a;
      //  if (f_x_y(x + 1, static_cast<float>(y) + 0.5f) < 0) {
      if (f_down < 0) {
        y++;
        f_down += b;
      }
    }

  }
  // slope ∈ (-1,0]
  else if (slope > -1.f) {
    // make sure p0.x <= p1.x
    if (p0.x > p1.x) {
      std::swap(p0, p1);
    }

    int y = std::round(p0.y);
    int const x1 = std::round(p1.x);

    int x = std::round(p0.x);

    float f_up = f_x_y(x + 1, static_cast<float>(y) + -0.5f);
    float a = (p0.y - p1.y), b = (p1.x - p0.x);

    for (; x <= x1; x++) {
      this->At(x, y) = line_color;
      f_up += a;
      // if (f_x_y(x + 1, static_cast<float>(y) + -0.5f) > 0) {
      if (f_up > 0) {
        y--;
        f_up -= b;
      }
    }

  }
  // slope ∈ [-inf,-1]
  else {
    // make sure p0.y <= p1.y
    if (p0.y > p1.y) {
      std::swap(p0, p1);
    }

    int x = std::round(p0.x);
    int const y1 = std::round(p1.y);

    int y = std::round(p0.y);

    float f_left = f_x_y(static_cast<float>(x) - 0.5f, y + 1);
    float a = (p0.y - p1.y), b = (p1.x - p0.x);

    for (; y <= y1; y++) {
      this->At(x, y) = line_color;
      f_left += b;

      //  if (f_x_y(static_cast<float>(x) - 0.5f, y + 1) < 0) {
      if (f_left < 0) {
        x--;
        f_left -= a;
      }
    }
  }
}
inline Image::Pixel &Image::At(unsigned x, unsigned y) {
  assert(x >= 0 && x < this->width);
  assert(y >= 0 && y < this->height);
  return (*this)[y][x];
}

void Image::Clear() {
  std::memset(data, 0,
              width * height * sizeof(Pixel) + height * scanline_stride);
}

Image Image::operator*(size_t const factor) {
  assert(width * factor / factor == width);   //"overflow"
  assert(height * factor / factor == height); //"overflow"
  auto XXL = Image(width * factor, height * factor);
  XXL.for_each_pixel_x_y([this, factor](Pixel &pixel, auto x, auto y) {
    pixel = (*this)[y / factor][x / factor];
  });
  return XXL;
}

size_t Image::GetDataSize() const {
  auto row_size = this->GetRowSize();
  auto data_size = this->height * row_size;
  return data_size;
}

size_t Image::GetRowSize() const {
  auto pixel_size = sizeof(Image::Pixel);
  return pixel_size * this->width + this->scanline_stride;
}

void Image::DrawTriangle(Vector2 a, Vector2 b, Vector2 c, const Color &a_color,
                         const Color &b_color, const Color &c_color) {
  DrawTriangle(a, b, c,
               [&](Image::Pixel &pixel, size_t, size_t, float alpha, float beta,
                   float gama) {
                 pixel = a_color * alpha + b_color * beta + c_color * gama;
               });
}

void Image::DrawTriangle(
    Vector2 a, Vector2 b, Vector2 c,
    std::function<void(Image::Pixel &, size_t, size_t, float, float,
                       float)> const &pixel_shader) {
  auto min_x =
      static_cast<unsigned>(std::round(std::min(std::min(a.x, b.x), c.x)));
  auto min_y =
      static_cast<unsigned>(std::round(std::min(std::min(a.y, b.y), c.y)));
  auto max_x =
      static_cast<unsigned>(std::round(std::max(std::max(a.x, b.x), c.x)));
  auto max_y =
      static_cast<unsigned>(std::round(std::max(std::max(a.y, b.y), c.y)));

  // incremental implicit line function value
  const float f_ab_xy_A = a.y - b.y, f_ab_xy_B = b.x - a.x,
              f_ab_xy_C = a.x * b.y - b.x * a.y;
  float f_ab_xy_dividend;
  float f_ab_xy_dividend_const = (f_ab_xy_A)*min_x + f_ab_xy_C;
  const float f_ab_xy_divisor =
      (f_ab_xy_A)*c.x + (f_ab_xy_B)*c.y + f_ab_xy_C; // fab_gama

  const float f_ac_xy_B = c.x - a.x, f_ac_xy_A = a.y - c.y,
              f_ac_xy_C = a.x * c.y - c.x * a.y;
  float f_ac_xy_dividend;
  float f_ac_xy_dividend_const = (f_ac_xy_A)*min_x + f_ac_xy_C;
  const float f_ac_xy_divisor =
      (f_ac_xy_A)*b.x + (f_ac_xy_B)*b.y + f_ac_xy_C; // fac_beta

  const float f_bc_xy_A = (b.y - c.y), f_bc_xy_B = (c.x - b.x),
              f_bc_xy_C = b.x * c.y - c.x * b.y;
  const float f_bc_xy_divisor =
      f_bc_xy_A * a.x + f_bc_xy_B * a.y + f_bc_xy_C; // fbc_alpha

  // off-screen point
  const float f_bc_offpt = f_bc_xy_A * -1.f + f_bc_xy_B * -1.f + f_bc_xy_C;
  const float f_ac_offpt = f_ac_xy_A * -1.f + f_ac_xy_B * -1.f + f_ac_xy_C;
  const float f_ab_offpt = f_ab_xy_A * -1.f + f_ab_xy_B * -1.f + f_ab_xy_C;
  const bool flag_same_side_alpha = f_bc_offpt * f_bc_xy_divisor > 0;
  const bool flag_same_side_beta = f_ac_offpt * f_ac_xy_divisor > 0;
  const bool flag_same_side_gama = f_ab_offpt * f_ab_xy_divisor > 0;

  for (auto y = min_y; y <= max_y; y++) {
    f_ab_xy_dividend = f_ab_xy_dividend_const + f_ab_xy_B * y;
    f_ac_xy_dividend = f_ac_xy_dividend_const + f_ac_xy_B * y;
    for (auto x = min_x; x <= max_x; x++) {
      float gama = f_ab_xy_dividend / f_ab_xy_divisor;
      // if (gama < 0) continue;  // todo why it's causing bug
      float beta = f_ac_xy_dividend / f_ac_xy_divisor;
      float alpha = 1.f - gama - beta;

      // if pixel center is inside the triangle or on the edges
      if (0.f <= alpha && 0.f <= beta && 0.f <= gama) {
        // if the pixel center is inside the triangle or on the same side with
        // the off-screen point (for the case pixel center on the edge)
        if ((flag_same_side_alpha || alpha > 0) &&
            (flag_same_side_beta || beta > 0) &&
            (flag_same_side_gama || gama > 0)) {
          pixel_shader((*this)[y][x], x, y, alpha, beta, gama);
        }
      }
      f_ab_xy_dividend += f_ab_xy_A;
      f_ac_xy_dividend += f_ac_xy_A;
    }
    f_ab_xy_dividend += f_ab_xy_B;
    f_ac_xy_dividend += f_ac_xy_B;
  }
}

void Image::for_each_pixel_x_y(
    std::function<void(Pixel &, unsigned, unsigned)> const &action) {
  auto pPixel = reinterpret_cast<Pixel *>(this->data);

  for (unsigned y = 0; y < this->height; y++) {
    for (unsigned x = 0; x < this->width; x++) {
      action(*pPixel, x, y);
      pPixel++;
    }
    // skip scanline stride
    pPixel = reinterpret_cast<Pixel *>(reinterpret_cast<char *>(pPixel) +
                                       this->scanline_stride);
  }
}

void Image::for_each_pixel_range_x_y(
    unsigned l, unsigned r, unsigned b, unsigned t,
    const std::function<void(Image::Pixel &, unsigned int, unsigned int)>
        &action) {
  for (auto y = b; y <= t; y++) {
    for (auto x = l; x <= r; x++) {
      action((*this)[y][x], x, y);
    }
  }
}

Matrix4 Image::GetMvp() {
  return Matrix4{Vector4{width / 2.f, 0, 0, 0}, Vector4{0, height / 2.f, 0, 0},
                 Vector4{0, 0, 1, 0},
                 Vector4{(width - 1) / 2.f, (height - 1) / 2.f, 0, 1}};
}

Color Color::operator*(const float k) const {
  auto r = std::roundf(this->r * k);
  if (r < 0)
    r = 0;
  if (r > 255)
    r = 255;
  auto g = std::roundf(this->g * k);
  if (g < 0)
    g = 0;
  if (g > 255)
    g = 255;
  auto b = std::roundf(this->b * k);
  if (b < 0)
    b = 0;
  if (b > 255)
    b = 255;
  return Color{static_cast<uint8_t>(r), static_cast<uint8_t>(g),
               static_cast<uint8_t>(b)};
}

Color Color::operator+(const Color &color) const {
  auto r = this->r + color.r;
  if (r > 255)
    r = 255;
  auto g = this->g + color.g;
  if (g > 255)
    g = 255;
  auto b = this->b + color.b;
  if (b > 255)
    b = 255;
  return Color{static_cast<uint8_t>(r), static_cast<uint8_t>(g),
               static_cast<uint8_t>(b)};
}

void Color::operator+=(const Color &color) { *this = (*this) + color; }

bool Color::operator==(const Color &B) const {
  return r == B.r && b == B.b && g == B.g;
}
