#pragma once
#include <pebble.h>
#include "console_window.h"

typedef struct ConsoleCursor {
  //! Show the console.
  void (*show)();
  
  //! Hide the console.
  void (*hide)();

  //! Set the console cursor position.
  //! @param x A column index
  //! @param y A row index
  void (*set_position)(uint8_t x, uint8_t y);
} ConsoleCursor;

ConsoleCursor console_cursor_create(Layer * parent_layer);

void console_cursor_destroy(ConsoleCursor console_cursor);