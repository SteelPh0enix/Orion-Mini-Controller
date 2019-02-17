#pragma once
#include <RF24.h>
#include "../../include/pinout.hpp"

/*
  Class used to communicate with rover
*/

class Communicator {
 public:
  void initialize();
  bool initialized() const;

  void send_data(char const* data, unsigned length);

  void print_debug_data();

 private:
  bool m_initialized{false};
  RF24 m_radio{Pin::RF24_ENABLE, Pin::RF24_SELECT};
};