#include <pebble.h>
#include "console_window.h"

ConsoleWindow consoleWindow;

void init(void) {
  //Create app elements here
  consoleWindow = console_window_create();
  consoleWindow.show();

  // Test
  consoleWindow.clear();
  consoleWindow.append("  *** C64 BASIC ***\n");
  consoleWindow.append(" %dK RAM SYSTEM\n", 64);
  consoleWindow.append("READY.\n");
  
  AppLaunchReason appLaunchReason = launch_reason();
  consoleWindow.append("LOAD \"%d\"\n", (int)appLaunchReason);
  
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
  consoleWindow.append("TIME: %02d:%02d\n", tick_time->tm_hour, tick_time->tm_min);
    
  for (int i = 32; i < 128; i++)
  {
    consoleWindow.append("%c,", i);
  }
  
  consoleWindow.append("\nREADY.\n");
  
  //consoleWindow.clear();
  //consoleWindow.append("");
  //consoleWindow.append("1\n11111111111111111123");
  consoleWindow.append("1234567890");
  consoleWindow.append("111111111111111111123\n\nREADY.\n");
}

void deinit(void) {
  //Destroy app elements here
  consoleWindow.hide();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
