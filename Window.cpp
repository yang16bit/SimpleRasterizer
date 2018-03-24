#include "Window.h"

#include <cassert>

#define WINDOW_CLASS_NAME L"TheWindowClass"

LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  if (auto window_ptr =
          reinterpret_cast<Window *>(GetWindowLongPtr(hwnd, GWLP_USERDATA))) {
    auto &window = *window_ptr;

    switch (msg) {
    case WM_PAINT:
      ////  beginpaint(); endpaint() // TODO: commented out, customizing for
      /// GameWindow
      ValidateRect(hwnd, NULL);
      return 0;

    case WM_SIZING:
      return TRUE;
    case WM_SIZE:
      // TODO resize
      // TODO cache GetWidth
      // ValidateRkect(hwnd, NULL);
      //        window.width = LOWORD(lparam);
      //        window.height = HIWORD(lparam);
      return 0;
    case WM_ERASEBKGND:
      return 1;

    case WM_ACTIVATE:
      //        if (wparam == WA_INACTIVE) {
      //          window.OnLoseFocus();
      //        } else {
      //          window.OnFocus();
      //        }
      break;

    case WM_DESTROY:
      window.destroyed = true;
      unclosed_wnd_counter--;
      //        PostQuitMessage(0);
      return 0;
      // Window closing steps :
      // - DefWindowProc detected user is closing window
      // - DefWindowProc post WM_SYSCOMMAND
      // - DefWindowProc post WM_CLOSE
      // - DefWindowProc call DestroyWindow()
      // - DestroyWindow clean it up and post WM_DESTROY
      // - programmer release resources and call PostQuitMessage()
      // - PostQuitMessage post WM_QUIT (it is not related to any window)
      // - GetMessage return 0
      // - ENDexit(0);

      // Ways to close window :
      // - PostQuitMessage(0);
      // - Post|SendMessage(WM_CLOSE,0,0);
      // - ExitProcess(0);
      // - exit(0) c-std-func

    case WM_KEYDOWN:
      window.OnKeyDown(wparam);
      switch (wparam) {
      case VK_ESCAPE:
        PostMessageW(window.hwnd, WM_CLOSE, 0, 0);
        return 0;
      }
    }
  }
  return ::DefWindowProc(hwnd, msg, wparam, lparam);
}

Window::Window(const unsigned int &width, const unsigned int &height) {
  static const wchar_t *window_class_name = [] {

    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_OWNDC;
    wcx.hInstance = module_handle;
    wcx.lpfnWndProc = &Window::WndProc;
    wcx.lpszClassName = WINDOW_CLASS_NAME;
    wcx.hbrBackground = NULL; // equals to case WM_ERASEBKGND:return 1;
    // wcx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    const auto result = ::RegisterClassEx(&wcx);
    assert(!FAILED(result));

    return wcx.lpszClassName;
  }();

  // extends width and height to the whole Window Rect
  const DWORD wnd_style = WS_OVERLAPPEDWINDOW;
  int client_width{}, client_height{};
  {
    RECT r{};
    r.right = width;
    r.bottom = height;
    AdjustWindowRect(&r, wnd_style, false);
    client_width = r.right - r.left;
    client_height = r.bottom - r.top;
  }
  hwnd = ::CreateWindow(window_class_name, L"", wnd_style, 0, 0, client_width,
                        client_height, NULL, NULL, module_handle, NULL);
  assert(hwnd); // err msg : CreateWindow call failed

  ::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

  unclosed_wnd_counter++;

  this->Center();

  ::ShowWindow(hwnd, SW_SHOW);
}

Window::~Window() {
  UnregisterClass(
      WINDOW_CLASS_NAME,
      module_handle); // TODO BUG, register once, unregister muti times
}

void Window::Update() {
  // process all msgs waiting in the queue
  static MSG msg{};
  if (idleMode) {
    WaitMessage();
  }
  while (PeekMessage(&msg, this->hwnd, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  if (!this->destroyed)
    this->OnPaint();
}

unsigned int Window::GetWidth() const {
  RECT rcClient;
  GetClientRect(hwnd, &rcClient);
  assert(rcClient.top == 0);
  assert(rcClient.left == 0);
  return rcClient.right;
}

unsigned int Window::GetHeight() const {
  RECT rcClient;
  GetClientRect(hwnd, &rcClient);
  assert(rcClient.top == 0);
  assert(rcClient.left == 0);
  return rcClient.bottom;
}

bool Window::SetTitle(const wchar_t *title) {
  return SetWindowText(hwnd, title);
}

bool Window::HasUnclosed() { return unclosed_wnd_counter; }

bool Window::Center() {
  assert(IsWindow(hwnd));
  RECT rcDesktopWorkArea; // desktop client rect, relative to screen rect
  ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktopWorkArea, 0);

  RECT rcWnd;
  ::GetWindowRect(hwnd, &rcWnd);

  const int w = rcWnd.right - rcWnd.left;
  const int h = rcWnd.bottom - rcWnd.top;
  const int x = (rcDesktopWorkArea.left + rcDesktopWorkArea.right - w) / 2;
  const int y = (rcDesktopWorkArea.top + rcDesktopWorkArea.bottom - h) / 2;

  return MoveWindow(hwnd, x, y, w, h, false);
}

// static member variables
HINSTANCE const Window::module_handle = GetModuleHandle(NULL);
unsigned Window::unclosed_wnd_counter = 0;
bool Window::idleMode{false};

void Window::OnPaint() {
  RECT rect;
  GetClientRect(hwnd, &rect);

  auto hdc = GetDC(hwnd);
  {
    static auto black_brush = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    FillRect(hdc, &rect, black_brush);
  }
  ReleaseDC(hwnd, hdc);
}

void Window::OnKeyDown(KeyCode kc) {
  auto iterResult = keydown_callbacks.find(kc);
  if (iterResult != keydown_callbacks.end()) {
    iterResult->second();
  }
}

// winmain
#ifdef _MSC_VER

extern int main();
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) { return main(); }
#endif