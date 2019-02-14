#include <Arduino.h>
#include <constants.hpp>
#include <pinout.hpp>

#include <switch.hpp>

Switch left{}, right{};

void setup() {
  Serial.begin(SerialConstants::BaudRate);

  left.set_pins(Pinout::TRIPOS_SWITCH_LEFT_DOWN, Pinout::TRIPOS_SWITCH_LEFT_UP);
  right.set_pins(Pinout::TRIPOS_SWITCH_RIGHT_DOWN,
                 Pinout::TRIPOS_SWITCH_RIGHT_UP);

  left.initialize();
  right.initialize();
}

void loop() {
  left.do_while_active([](Switch::State state) {
    Serial.print("Left switch state: ");
    switch (state) {
      case Switch::State::Up:
        Serial.println("Up");
        break;
      case Switch::State::Down:
        Serial.println("Down");
        break;
      default:
        break;
    }
  });

  right.do_while_active([](Switch::State state) {
    Serial.print("Right switch state: ");
    switch (state) {
      case Switch::State::Up:
        Serial.println("Up");
        break;
      case Switch::State::Down:
        Serial.println("Down");
        break;
      default:
        break;
    }
  });

  delay(50);
}
