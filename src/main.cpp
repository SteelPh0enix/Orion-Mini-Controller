#include <Arduino.h>
#include <JsonDataParser.hpp>
#include <constants.hpp>
#include <controller.hpp>

Controller controller;
JsonDataParser parser;
char data_buffer[JsonDataParser::BufferSize];

bool serial_state{SerialConstant::EnabledByDefault};

void setup() {
  Serial.begin(SerialConstant::BaudRate);
  controller.initialize();
}

void loop() {
  if (controller.get_button(Controller::Button1)->pressed()) {
    parser.parse_command(Command::Stop, data_buffer);
    controller.calibrate();
  } else {
    parser.parse_movement(controller, data_buffer);
  }
}