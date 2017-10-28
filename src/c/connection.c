#include <pebble.h>
#include "connection.h"

Connection get_connection(void *context) {
  Connection *connection = (Connection*)context;
  return *connection;  
}

static void inbox_received_handler(DictionaryIterator *iterator, void *context) {
  get_connection(context).message_received_handler("received 3");
  
  // Get the first pair
  Tuple *t = dict_read_first(iterator);

  // Process all pairs present
  while(t != NULL) {
    // Process this pair's key
    switch(t->key) {
      //case KEY_VIBRATE:
        // Trigger vibration
        //vibes_short_pulse();
        //break;
      //case KEY_CHAR:
        //console_write(t->value->cstring);
        //break;
      //case KEY_MESSAGE:
        //console_write_line(t->value->cstring);
        //break;
      default:
        APP_LOG(APP_LOG_LEVEL_INFO, "Message received. Key: '%d'", (int)t->key);
        Connection connection = (*(Connection*)context);
        if (connection.message_received_handler) {
          connection.message_received_handler("xxx");
        }
        
        break;
    }

    // Get next pair, if any
    t = dict_read_next(iterator);
  }
}

static void inbox_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message dropped!");
  get_connection(context).message_received_handler("received 5");
}

static void outbox_failed_handler(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send failed!");
  get_connection(context).message_received_handler("received 4");
}

void outbox_sent_handler(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message sent.");
  //TODO:
  //get_connection(context).message_received_handler("received 2");
  //get_connection(app_message_get_context()).message_received_handler("received 2");
  APP_LOG(APP_LOG_LEVEL_ERROR, "Connection");
}

void destroy() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "connection.destroy");
  app_message_deregister_callbacks();
}

void send(const char *message) {
  uint32_t key = 1;
  
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  //dict_write_int(iter, key, &message, sizeof(int), true);
  app_message_outbox_send();
}

void open_connection(void *context) {
  get_connection(context).message_received_handler("received 1");

  // Register callbacks  
  app_message_set_context(context);
  app_message_register_inbox_received(inbox_received_handler);
  app_message_register_inbox_dropped(inbox_dropped_handler);
  app_message_register_outbox_failed(outbox_failed_handler);
  app_message_register_outbox_sent(outbox_sent_handler);

  // Open AppMessage
  //app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  app_message_open(APP_MESSAGE_INBOX_SIZE_MINIMUM, APP_MESSAGE_OUTBOX_SIZE_MINIMUM);
}
  
Connection connection_create(MessageReceivedHandler message_received_handler)
{
  Connection connection = (Connection) {
    //.open = open_connection,
    .send = send,
    .message_received_handler = message_received_handler,
    .destroy = destroy
  };
  
  open_connection(&connection);
  
  return connection;
}