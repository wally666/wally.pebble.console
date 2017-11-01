#include <pebble.h>
#include "console_window.h"
#include "connection.h"

ConsoleWindow consoleWindow;
Connection connection;

void message_received_handler(const char *message)
{
  APP_LOG(APP_LOG_LEVEL_DEBUG, message);
  consoleWindow.append(message);
}

void init(void) {
  //Create app elements here
  consoleWindow = console_window_create();
  consoleWindow.show();

  // Test
  consoleWindow.clear();
  consoleWindow.append("  *** C64 BASIC ***\n");
  size_t ram_free = heap_bytes_free();
  size_t ram_used = heap_bytes_used();
  consoleWindow.append(" %3.2fK RAM, %dB FREE, %dB USED\n", (ram_free + ram_used) / 1024, ram_free, ram_used);
  consoleWindow.append("READY.\n");
  
  AppLaunchReason appLaunchReason = launch_reason();
  consoleWindow.append("LOAD \"%d\"\n", (int)appLaunchReason);
  
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
  consoleWindow.append("TIME: %02d:%02d\n", tick_time->tm_hour, tick_time->tm_min);
  /* 
  for (int i = 1; i < 128; i++)
  {
    consoleWindow.append("%c,", i);
  }
  */
  /*
  consoleWindow.append("\n10 PRINT HELLO WORD!\n");
  consoleWindow.append("LIST 10\n");
  consoleWindow.append("10 PRINT HELLO WORD!\n");
  consoleWindow.append("RUN\n");
  consoleWindow.append("HELLO WORD!\n");
  */
  consoleWindow.append("READY.\n");
  consoleWindow.append("LOAD \"BATTERY STATE\"\n");
  BatteryChargeState battery = battery_state_service_peek();
  consoleWindow.append("BATTERY STATE=%d%%\n", (int)battery.charge_percent);
  
  connection = connection_create(message_received_handler);
  connection.send("TEST: SEND");
  connection.message_received_handler("TEST: RECEIVED");
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
