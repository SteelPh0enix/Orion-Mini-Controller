#include <Arduino.h>
#include <constants.hpp>

bool serial_state{SerialConstants::EnabledByDefault};

void setup() { Serial.begin(SerialConstants::BaudRate); }

void loop() {}