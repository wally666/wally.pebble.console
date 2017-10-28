#pragma once
#include <stdarg.h>

typedef struct ConsoleWindow {
  //! Show the console.
  void (*show)();
  
  //! Hide the console.
  void (*hide)();

  //! Send a text to the console.
  //! @param fmt A C formatting string
  //! @param ... The arguments for the formatting string
  //! \sa snprintf for details about the C formatting string.
  void (*append)(const char* fmt, ...);
  
  //! Clean the console.
  void (*clear)();
  
  //! Set the console cursor position.
  //! @param x A column index
  //! @param y A row index
  void (*set_cursor_pos)(uint8_t x, uint8_t y);
} ConsoleWindow;

ConsoleWindow console_window_create(void);