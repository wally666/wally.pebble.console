#pragma once

//typedef void(* AppMessageInboxReceived)(DictionaryIterator *iterator, void *context)
typedef void(* MessageReceivedHandler)(const int key, const char *message);
  
typedef struct Connection {
  //! Send the message to phone.
  void (*send)(const char *message);
  
  //! New message receive handler.
  MessageReceivedHandler message_received_handler;
  
  void (*destroy)();
} Connection;

Connection connection_create();