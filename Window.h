#pragma once

#ifndef CH8_WINDOW_H
#define CH8_WINDOW_H

#define WIN32_LEAN_AND_MEAN
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>

#include "KeyCode.h"
#include <functional>
#include <map>

class Window {
public:
  Window(const unsigned int &width = 1280, const unsigned int &height = 720);
  virtual ~Window();
  void Update();

  unsigned int GetWidth() const;
  unsigned int GetHeight() const;
  bool SetTitle(const wchar_t *title);

  static bool idleMode;
  static bool HasUnclosed();

protected:
  HWND hwnd{};

  // handle of the process
  static HINSTANCE const module_handle;

  bool Center();

  virtual void OnPaint();
  virtual void OnKeyDown(KeyCode kc);
  std::map<KeyCode, std::function<void()>> keydown_callbacks;
  bool destroyed = false;

private:
  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam,
                                  LPARAM lparam);

  static unsigned unclosed_wnd_counter;
};

#endif // CH8_WINDOW_H
