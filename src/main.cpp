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
  controller.get_button(Controller::Button1)->do_if_pressed([&] {
    parser.parse_command(Command::Stop, data_buffer);
    comms.send_data(data_buffer, strlen(data_buffer));
    if (serial_state) {
      Serial.println(data_buffer);
    }
    controller.calibrate();
  });

  controller.get_button(Controller::Button4)->do_if_pressed([&] {
    comms.print_debug_data();
  });

  controller.get_button(Controller::Button5)->do_if_pressed([&] {
    serial_state = !serial_state;
  });

  parser.parse_movement(controller, data_buffer);
  comms.send_data(data_buffer, strlen(data_buffer));

  if (serial_state) {
    Serial.println(data_buffer);
  }
}