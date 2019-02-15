#pragma once
#include <Arduino.h>
#include <map>
#include <pinout.hpp>

/*
  Main class of the remote controller
*/

class Controller {
 public:
  Controller();
  void initialize();

 private:
  bool m_initialized{false};
};