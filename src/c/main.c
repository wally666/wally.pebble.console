#include <pebble.h>
#include "console_window.h"
#include "connection.h"

ConsoleWindow consoleWindow;
Connection connection;

void message_received_handler(const int key, const char *message)
{
  APP_LOG(APP_LOG_LEVEL_DEBUG, message);
  consoleWindow.append("MESSAGE '%d' RECEIVED:\n%s\n", key, message);
}

void init(void) {
  //Create app elements here
  consoleWindow = console_window_create();
  consoleWindow.show();

  // Test
  consoleWindow.clear();
  consoleWindow.append("  *** C64 BASIC ***\n");
  size_t ram_free = heap_bytes_free() / 1024;
  size_t ram_used = heap_bytes_used() / 1024;
  consoleWindow.append("%dK/%dK RAM FREE\n\n", ram_free, ram_free + ram_used);
  consoleWindow.append("READY.\n");
  
  AppLaunchReason appLaunchReason = launch_reason();
  consoleWindow.append("LOAD \"%d\"\n", (int)appLaunchReason);
  
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
  consoleWindow.append("TIME: %02d:%02d\n\n", tick_time->tm_hour, tick_time->tm_min);
  /* 
  for (int i = 1; i < 128; i++)
  {
    consoleWindow.append("%c,", i);
  }
  */
  consoleWindow.append("READY.\n");
  consoleWindow.append("LOAD \"BATTERY STATE\"\n");
  BatteryChargeState battery = battery_state_service_peek();
  consoleWindow.append("BATTERY STATE=%d%%\n", (int)battery.charge_percent);
  
  connection = connection_create(message_received_handler);
  // connection.send("TEST: SEND");
}

void deinit(void) {
  //Destroy app elements here
  connection.destroy();
  consoleWindow.hide();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
