#include "CanvasWindow.h"

class TriangleShow : CanvasWindow {
public:
  TriangleShow() : CanvasWindow(1000, 1000) {
    // TODO explicitly use half transparent white color
    canvas.DrawTriangle(Vector2{300, 0}, Vector2{600, 700}, Vector2{150, 336});
    canvas.DrawTriangle(Vector2{300, 0}, Vector2{800, 800}, Vector2{600, 700});
  }
  void Start() {
    Window::idleMode = true;
    while (Window::HasUnclosed()) {
      this->Update();
    }
  }
};

int main() {
  TriangleShow app;
  app.Start();
}