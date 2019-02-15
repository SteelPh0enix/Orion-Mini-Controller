#include <Arduino.h>
#include <constants.hpp>
#include <controller.hpp>

Controller controller;

bool serial_state{SerialConstants::EnabledByDefault};

void setup() {
  Serial.begin(SerialConstants::BaudRate);
  controller.initialize();
}

void loop() {}