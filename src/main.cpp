#include <Arduino.h>
#include <JsonDataParser.hpp>
#include <communicator.hpp>
#include <constants.hpp>
#include <controller.hpp>

Controller controller;
JsonDataParser parser;
Communicator comms;
char data_buffer[JsonDataParser::BufferSize];

bool serial_state{SerialConstant::EnabledByDefault};

void setup() {
  Serial.begin(SerialConstant::BaudRate);
  controller.initialize();
  comms.initialize();
}

void loop() {
  if (controller.get_button(Controller::Button1)->pressed()) {
    parser.parse_command(Command::Stop, data_buffer);
    controller.calibrate();
  } else if (controller.get_button(Controller::Button2)->pressed()) {
    comms.print_debug_data();
  } else if (controller.get_button(Controller::Button5)->pressed()) {
    serial_state = !serial_state;
  } else {
    parser.parse_movement(controller, data_buffer);
  }

  comms.send_data(data_buffer, strlen(data_buffer));

  if (serial_state) {
    Serial.println(data_buffer);
  }
}