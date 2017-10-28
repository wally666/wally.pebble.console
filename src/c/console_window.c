#include <pebble.h>
#include <stdarg.h>
#include "mini-printf.h"
#include "console_window.h"
#include "console_cursor.h"

#define MAX_CURSOR_X 20
#define MAX_CURSOR_Y 30

Window *window;
TextLayer *text_layer;
GFont font;
char *text = NULL;
size_t text_len = 0;
ConsoleCursor cursor;

void append(const char*	fmt,	...) {
  size_t buffer_size = MAX_CURSOR_X * MAX_CURSOR_Y;
  char buffer[buffer_size];

  va_list va;
	va_start(va, fmt);
  mini_vsnprintf(buffer, buffer_size, fmt, va);
 	va_end(va);

  text = strcat(text, buffer);
  
  // Update
  text_layer_set_text(text_layer, text);
  //layer_mark_dirty(text_layer_get_layer(text_layer));
  
  cursor.set_position(0, 17);
}

void window_load(Window *window) {
  // We will add the creation of the Window's elements here soon!
  APP_LOG(APP_LOG_LEVEL_ERROR, "window_load");
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  
  // Initialize the text layer
  text_layer = text_layer_create(bounds);
  //text_layer_set_background_color(text_layer, GColorBlack);
  //text_layer_set_text_color(text_layer, GColorWhite);
  //text_layer_set_overflow_mode(text_layer, GTextOverflowModeWordWrap);
  //text_layer_set_overflow_mode(text_layer, GTextOverflowModeTrailingEllipsis);
  //text_layer_set_overflow_mode(text_layer, GTextOverflowModeFill);
  font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_COMMODORE_8));
  text_layer_set_font(text_layer, font);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
  
  text = malloc(MAX_CURSOR_Y * (MAX_CURSOR_X + 1));
  
  cursor = console_cursor_create(text_layer_get_layer(text_layer));
  cursor.show();
}

void window_unload(Window *window) {
  //We will safely destroy the Window's elements here!
  APP_LOG(APP_LOG_LEVEL_ERROR, "window_unload");

  // Destroy app elements here
  APP_LOG(APP_LOG_LEVEL_ERROR, "deinit_console_window");
  console_cursor_destroy(cursor);
  text_layer_destroy(text_layer);
  fonts_unload_custom_font(font);
  window_destroy(window);
  free(text);
}

void show(void) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "show_console_window");
 
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });

  //window_set_background_color(window, GColorBlack); 
  window_stack_push(window, true);
}

void hide(void) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "hide_console_window");
  window_stack_remove(window, true);
}

void clear(void) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "clear");
  cursor.set_position(0, 0);
  text_len = 0;
  text[0] = '\0';
  layer_mark_dirty(text_layer_get_layer(text_layer));
}

ConsoleWindow console_window_create(void) {
  return (ConsoleWindow) {
    .show = show,
    .hide = hide,
    .append = append,
    .clear = clear
  };
}