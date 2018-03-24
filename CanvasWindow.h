#ifndef CH8_CANVASWINDOW_H
#define CH8_CANVASWINDOW_H

#include "Image.h"
#include "Window.h"

class CanvasWindow : public Window {
public:
  CanvasWindow(const unsigned int &width = 1280,
               const unsigned int &height = 720);
  virtual ~CanvasWindow();

protected:
  Image canvas;
  virtual void OnPaint();

private:
};

#endif // CH8_CANVASWINDOW_H
