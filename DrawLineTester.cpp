#include "CanvasWindow.h"

#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class DrawLine_Tester : public CanvasWindow {
public:
  DrawLine_Tester() : CanvasWindow(1000, 1000) {
    // response to key
    this->keydown_callbacks.insert(
        std::make_pair(KC_SPACE, [this] { this->PaintCanvas(); }));
  }
  void Start() {
    Window::idleMode = true;
    this->SetTitle(L"press [space]");
    while (Window::HasUnclosed()) {
      this->Update();
    }
  }

private:
  void PaintCanvas() {
    static int count = 0;
    count++;
    canvas.Clear();
    // draw lines
    {
      float r = 400;
      Vector2 displacement{this->GetWidth() / 2.f - 1.f,
                           this->GetHeight() / 2.f - 1.f};
      auto count_cpy = count;
      float sloap;
      Vector2 p0, p1;
      for (float alpha = 0.f; alpha <= 2.f * M_PI;
           alpha += (float)M_PI * (1.f / 8.f)) {
        if (count_cpy <= 0)
          break;
        p0 = displacement;
        p1 = displacement + Vector2{std::cos(alpha) * r, std::sin(alpha) * r};
        canvas.DrawLine(p0, p1);
        sloap = (p1.y - p0.y) / (p1.x - p0.x);

        count_cpy--;
      }

      // update title
      {
        wchar_t buf[1024];
        p0 -= displacement;
        p1 -= displacement;
        swprintf(buf, sizeof(buf) / sizeof(decltype(buf[0])),
                 L"(%f,%f)(%f,%f)%f", p0.x, p0.y, p1.x, p1.y, sloap);
        this->SetTitle(buf);
      }
    }
  }
};

int main() {
  DrawLine_Tester tester;
  tester.Start();
  return 0;
}