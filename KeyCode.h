#ifndef CH8_KEYCODE_H
#define CH8_KEYCODE_H

// WIN32
#if !defined _WIN32 && !defined _WIN64
#error __FILE__(__LINE__) : KeyCode.h for Windows included when targetting non-Windows platform
#endif // !defined _WIN32 && !defined _WIN64

typedef unsigned KeyCode;

#define KC_LBUTTON ((KeyCode)0x01)  // Left mouse button
#define KC_RBUTTON ((KeyCode)0x02)  // Right mouse button
#define KC_CANCEL ((KeyCode)0x03)   // Control-break processing
#define KC_MBUTTON ((KeyCode)0x04)  // Middle mouse button (three-button mouse)
#define KC_XBUTTON1 ((KeyCode)0x05) // X1 mouse button
#define KC_XBUTTON2 ((KeyCode)0x06) // X2 mouse button
#define KC_BACK ((KeyCode)0x08)     // BACKSPACE key
#define KC_TAB ((KeyCode)0x09)      // TAB key
#define KC_CLEAR ((KeyCode)0x0C)    // CLEAR key
#define KC_RETURN ((KeyCode)0x0D)   // ENTER key
#define KC_SHIFT ((KeyCode)0x10)    // SHIFT key
#define KC_CONTROL ((KeyCode)0x11)  // CTRL key
#define KC_MENU ((KeyCode)0x12)     // ALT key
#define KC_PAUSE ((KeyCode)0x13)    // PAUSE key
#define KC_CAPITAL ((KeyCode)0x14)  // CAPS LOCK key
#define KC_KANA ((KeyCode)0x15)     // IME Kana mode
#define KC_HANGUEL                                                             \
  ((KeyCode)0x15) // IME Hanguel mode (maintained for compatibility; use
                  // VK_HANGUL)
#define KC_HANGUL ((KeyCode)0x15)       // IME Hangul mode
#define KC_JUNJA ((KeyCode)0x17)        // IME Junja mode
#define KC_FINAL ((KeyCode)0x18)        // IME final mode
#define KC_HANJA ((KeyCode)0x19)        // IME Hanja mode
#define KC_KANJI ((KeyCode)0x19)        // IME Kanji mode
#define KC_ESCAPE ((KeyCode)0x1B)       // ESC key
#define KC_CONVERT ((KeyCode)0x1C)      // IME convert
#define KC_NONCONVERT ((KeyCode)0x1D)   // IME nonconvert
#define KC_ACCEPT ((KeyCode)0x1E)       // IME accept
#define KC_MODECHANGE ((KeyCode)0x1F)   // IME mode change request
#define KC_SPACE ((KeyCode)0x20)        // SPACEBAR
#define KC_PRIOR ((KeyCode)0x21)        // PAGE UP key
#define KC_NEXT ((KeyCode)0x22)         // PAGE DOWN key
#define KC_END ((KeyCode)0x23)          // END key
#define KC_HOME ((KeyCode)0x24)         // HOME key
#define KC_LEFT ((KeyCode)0x25)         // LEFT ARROW key
#define KC_UP ((KeyCode)0x26)           // UP ARROW key
#define KC_RIGHT ((KeyCode)0x27)        // RIGHT ARROW key
#define KC_DOWN ((KeyCode)0x28)         // DOWN ARROW key
#define KC_SELECT ((KeyCode)0x29)       // SELECT key
#define KC_PRINT ((KeyCode)0x2A)        // PRINT key
#define KC_EXECUTE ((KeyCode)0x2B)      // EXECUTE key
#define KC_SNAPSHOT ((KeyCode)0x2C)     // PRINT SCREEN key
#define KC_INSERT ((KeyCode)0x2D)       // INS key
#define KC_DELETE ((KeyCode)0x2E)       // DEL key
#define KC_HELP ((KeyCode)0x2F)         // HELP key
#define KC_LWIN ((KeyCode)0x5B)         // Left Windows key (Natural keyboard)
#define KC_RWIN ((KeyCode)0x5C)         // Right Windows key (Natural keyboard)
#define KC_APPS ((KeyCode)0x5D)         // Applications key (Natural keyboard)
#define KC_SLEEP ((KeyCode)0x5F)        // Computer Sleep key
#define KC_NUMPAD0 ((KeyCode)0x60)      // Numeric keypad 0 key
#define KC_NUMPAD1 ((KeyCode)0x61)      // Numeric keypad 1 key
#define KC_NUMPAD2 ((KeyCode)0x62)      // Numeric keypad 2 key
#define KC_NUMPAD3 ((KeyCode)0x63)      // Numeric keypad 3 key
#define KC_NUMPAD4 ((KeyCode)0x64)      // Numeric keypad 4 key
#define KC_NUMPAD5 ((KeyCode)0x65)      // Numeric keypad 5 key
#define KC_NUMPAD6 ((KeyCode)0x66)      // Numeric keypad 6 key
#define KC_NUMPAD7 ((KeyCode)0x67)      // Numeric keypad 7 key
#define KC_NUMPAD8 ((KeyCode)0x68)      // Numeric keypad 8 key
#define KC_NUMPAD9 ((KeyCode)0x69)      // Numeric keypad 9 key
#define KC_MULTIPLY ((KeyCode)0x6A)     // Multiply key
#define KC_ADD ((KeyCode)0x6B)          // Add key
#define KC_SEPARATOR ((KeyCode)0x6C)    // Separator key
#define KC_SUBTRACT ((KeyCode)0x6D)     // Subtract key
#define KC_DECIMAL ((KeyCode)0x6E)      // Decimal key
#define KC_DIVIDE ((KeyCode)0x6F)       // Divide key
#define KC_F1 ((KeyCode)0x70)           // F1 key
#define KC_F2 ((KeyCode)0x71)           // F2 key
#define KC_F3 ((KeyCode)0x72)           // F3 key
#define KC_F4 ((KeyCode)0x73)           // F4 key
#define KC_F5 ((KeyCode)0x74)           // F5 key
#define KC_F6 ((KeyCode)0x75)           // F6 key
#define KC_F7 ((KeyCode)0x76)           // F7 key
#define KC_F8 ((KeyCode)0x77)           // F8 key
#define KC_F9 ((KeyCode)0x78)           // F9 key
#define KC_F10 ((KeyCode)0x79)          // F10 key
#define KC_F11 ((KeyCode)0x7A)          // F11 key
#define KC_F12 ((KeyCode)0x7B)          // F12 key
#define KC_F13 ((KeyCode)0x7C)          // F13 key
#define KC_F14 ((KeyCode)0x7D)          // F14 key
#define KC_F15 ((KeyCode)0x7E)          // F15 key
#define KC_F16 ((KeyCode)0x7F)          // F16 key
#define KC_F17 ((KeyCode)0x80)          // F17 key
#define KC_F18 ((KeyCode)0x81)          // F18 key
#define KC_F19 ((KeyCode)0x82)          // F19 key
#define KC_F20 ((KeyCode)0x83)          // F20 key
#define KC_F21 ((KeyCode)0x84)          // F21 key
#define KC_F22 ((KeyCode)0x85)          // F22 key
#define KC_F23 ((KeyCode)0x86)          // F23 key
#define KC_F24 ((KeyCode)0x87)          // F24 key
#define KC_NUMLOCK ((KeyCode)0x90)      // NUM LOCK key
#define KC_SCROLL ((KeyCode)0x91)       // SCROLL LOCK key
#define KC_LSHIFT ((KeyCode)0xA0)       // Left SHIFT key
#define KC_RSHIFT ((KeyCode)0xA1)       // Right SHIFT key
#define KC_LCONTROL ((KeyCode)0xA2)     // Left CONTROL key
#define KC_RCONTROL ((KeyCode)0xA3)     // Right CONTROL key
#define KC_LMENU ((KeyCode)0xA4)        // Left MENU key
#define KC_RMENU ((KeyCode)0xA5)        // Right MENU key
#define KC_BROWSER_BACK ((KeyCode)0xA6) // Browser Back key
#define KC_BROWSER_FORWARD ((KeyCode)0xA7)     // Browser Forward key
#define KC_BROWSER_REFRESH ((KeyCode)0xA8)     // Browser Refresh key
#define KC_BROWSER_STOP ((KeyCode)0xA9)        // Browser Stop key
#define KC_BROWSER_SEARCH ((KeyCode)0xAA)      // Browser Search key
#define KC_BROWSER_FAVORITES ((KeyCode)0xAB)   // Browser Favorites key
#define KC_BROWSER_HOME ((KeyCode)0xAC)        // Browser Start and Home key
#define KC_VOLUME_MUTE ((KeyCode)0xAD)         // Volume Mute key
#define KC_VOLUME_DOWN ((KeyCode)0xAE)         // Volume Down key
#define KC_VOLUME_UP ((KeyCode)0xAF)           // Volume Up key
#define KC_MEDIA_NEXT_TRACK ((KeyCode)0xB0)    // Next Track key
#define KC_MEDIA_PREV_TRACK ((KeyCode)0xB1)    // Previous Track key
#define KC_MEDIA_STOP ((KeyCode)0xB2)          // Stop Media key
#define KC_MEDIA_PLAY_PAUSE ((KeyCode)0xB3)    // Play/Pause Media key
#define KC_LAUNCH_MAIL ((KeyCode)0xB4)         // Start Mail key
#define KC_LAUNCH_MEDIA_SELECT ((KeyCode)0xB5) // Select Media key
#define KC_LAUNCH_APP1 ((KeyCode)0xB6)         // Start Application 1 key
#define KC_LAUNCH_APP2 ((KeyCode)0xB7)         // Start Application 2 key
#define KC_OEM_1                                                               \
  ((KeyCode)0xBA) // Used for miscellaneous characters; it can vary by
                  // keyboard.
#define KC_OEM_PLUS ((KeyCode)0xBB)   // For any country/region, the '+' key
#define KC_OEM_COMMA ((KeyCode)0xBC)  // For any country/region, the ',' key
#define KC_OEM_MINUS ((KeyCode)0xBD)  // For any country/region, the '-' key
#define KC_OEM_PERIOD ((KeyCode)0xBE) // For any country/region, the '.' key
#define KC_OEM_2                                                               \
  ((KeyCode)0xBF) // Used for miscellaneous characters; it can vary by
                  // keyboard.
#define KC_OEM_3                                                               \
  ((KeyCode)0xC0) // Used for miscellaneous characters; it can vary by
                  // keyboard.
#define KC_OEM_4                                                               \
  ((KeyCode)0xDB) // Used for miscellaneous characters; it can vary by
                  // keyboard.
#define KC_OEM_5                                                               \
  ((KeyCode)0xDC) // Used for miscellaneous characters; it can vary by
                  // keyboard.
#define KC_OEM_6                                                               \
  ((KeyCode)0xDD) // Used for miscellaneous characters; it can vary by
                  // keyboard.
#define KC_OEM_7                                                               \
  ((KeyCode)0xDE) // Used for miscellaneous characters; it can vary by
                  // keyboard.
#define KC_OEM_8                                                               \
  ((KeyCode)0xDF) // Used for miscellaneous characters; it can vary by
                  // keyboard.
#define KC_OEM_102                                                             \
  ((KeyCode)0xE2) // Either the angle bracket key or the backslash key on the
                  // RT 102-key keyboard
#define KC_PROCESSKEY ((KeyCode)0xE5) // IME PROCESS key
#define KC_PACKET                                                              \
  ((KeyCode)0xE7) // Used to pass Unicode characters as if they were
                  // keystrokes. The VK_PACKET key is the low word of a 32-bit
                  // Virtual Key value used for non-keyboard input methods. For
                  // more information, see Remark in KEYBDINPUT, SendInput,
                  // WM_KEYDOWN, and WM_KEYUP
#define KC_ATTN ((KeyCode)0xF6)      // Attn key
#define KC_CRSEL ((KeyCode)0xF7)     // CrSel key
#define KC_EXSEL ((KeyCode)0xF8)     // ExSel key
#define KC_EREOF ((KeyCode)0xF9)     // Erase EOF key
#define KC_PLAY ((KeyCode)0xFA)      // Play key
#define KC_ZOOM ((KeyCode)0xFB)      // Zoom key
#define KC_NONAME ((KeyCode)0xFC)    // Reserved
#define KC_PA1 ((KeyCode)0xFD)       // PA1 key
#define KC_OEM_CLEAR ((KeyCode)0xFE) // Clear key

#endif // CH8_KEYCODE_H
