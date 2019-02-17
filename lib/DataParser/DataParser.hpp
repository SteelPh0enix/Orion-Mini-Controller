#pragma once
#include <Arduino.h>
#include "../../include/constants.hpp"
/*
  Interface for class parsing data from Controller
*/

class Controller;

class DataParser {
 public:
  virtual void parse_movement(Controller const& controler, char* buffer) = 0;
  virtual void parse_command(Command command, char* buffer) = 0;
};