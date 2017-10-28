#pragma once

//typedef void(* AppMessageInboxReceived)(DictionaryIterator *iterator, void *context)
typedef void(* MessageReceivedHandler)(const char *message);
  
typedef struct Connection {
  //! Opens the connection.
  void (*open)();
  //! Send the message to phone.
  void (*send)(const char *message);
  
  //! New message receive handler.
  MessageReceivedHandler message_received_handler;
  
  void (*destroy)();
} Connection;

Connection connection_create();

// void connection_destroy(Connection connection);
