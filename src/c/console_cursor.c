#include <pebble.h>
#include "console_cursor.h"

TextLayer *cursor_layer;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
Animation *animation;
AnimationImplementation animation_implementation;
bool isCursorHidden = true;

void animation_setup(Animation *animation) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Animation started!");
}

void animation_update(Animation *animation, const AnimationProgress progress) {
  // Animate some completion variable
  //int animation_percent = ((int)progress * 100) / ANIMATION_NORMALIZED_MAX;
  //APP_LOG(APP_LOG_LEVEL_INFO, "Animation progress: %d%%", animation_percent);
  //APP_LOG(APP_LOG_LEVEL_INFO, "Progress: %d", (int)progress);
  if (progress > 65535 / 2 && isCursorHidden)
  {
    isCursorHidden = !isCursorHidden;
    layer_set_hidden((Layer *)cursor_layer, isCursorHidden);
  } 
  else if (progress <= 65535 / 2 && !isCursorHidden) 
  {
    isCursorHidden = !isCursorHidden;
    layer_set_hidden((Layer *)cursor_layer, isCursorHidden);
  }
}

void animation_teardown(Animation *animation) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Animation finished!");
}

void cursor_show() {
  animation = animation_create();
  animation_set_duration(animation, 500);
  animation_set_delay(animation, 0);
  animation_implementation = (AnimationImplementation) {
    .setup = animation_setup,
    .update = animation_update,
    .teardown = animation_teardown
  };
  animation_set_implementation(animation, &animation_implementation);
  animation_set_play_count(animation, ANIMATION_PLAY_COUNT_INFINITE);
  animation_schedule(animation);
}

void set_position(uint8_t x, uint8_t y) {
  cursor_x = x;
  cursor_y = y;
  
  layer_set_bounds((Layer *)cursor_layer, GRect(cursor_x * 4, cursor_y * 4, 8, 8));
}

ConsoleCursor console_cursor_create(Layer * parent_layer) {
  GRect bounds = layer_get_bounds(parent_layer);
  cursor_layer = text_layer_create(bounds);
  text_layer_set_background_color(cursor_layer, GColorBlack);
  layer_add_child(parent_layer, text_layer_get_layer(cursor_layer));
  
  return (ConsoleCursor) {
    .show = cursor_show,
    .set_position = set_position
  };
}

void console_cursor_destroy(ConsoleCursor console_cursor) {
  animation_destroy(animation);
  text_layer_destroy(cursor_layer);
}