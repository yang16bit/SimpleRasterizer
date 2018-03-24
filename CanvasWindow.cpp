#include "CanvasWindow.h"
#include <cassert>

CanvasWindow::CanvasWindow(const unsigned int &width,
                           const unsigned int &height)
    : Window(width, height), canvas(width, height) {}

// blit canvas to window
void CanvasWindow::OnPaint() {
  auto &width = canvas.width;
  auto &height = canvas.height;
  auto &bits = canvas.data;

  assert(IsWindow(this->hwnd));
  static HDC hdcClient = GetDC(this->hwnd);
  static BITMAPINFO BMInfo{
      {sizeof(BITMAPINFOHEADER), 0, 0, 1, 24, BI_RGB, 0, 0, 0, 0, 0},
      {{0, 0, 0, 0}}};
  BMInfo.bmiHeader.biWidth = static_cast<long>(width);
  BMInfo.bmiHeader.biHeight = static_cast<long>(height);
  auto r = SetDIBitsToDevice(hdcClient, 0, 0, // destination X Y
                             width, height,   // source W H
                             0, 0,            // source X Y
                             0,               // 1st scan line
                             height,          // number of all scan lines
                             bits, &BMInfo,
                             0 // don't care
  );
  assert(r == (int)height);
}

CanvasWindow::~CanvasWindow() {}
