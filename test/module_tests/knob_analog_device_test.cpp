#include <Arduino.h>
#include <constants.hpp>
#include <pinout.hpp>

#include <knob.hpp>

Knob top_left, top_right, front_left, front_right;

Knob* knobs[4]{&top_left, &top_right, &front_left, &front_right};

void setup() {
  Serial.begin(SerialConstants::BaudRate);

  top_left.set_pins(Pinout::KNOB_TOP_LEFT);
  top_right.set_pins(Pinout::KNOB_TOP_RIGHT);
  front_left.set_pins(Pinout::KNOB_FRONT_LEFT);
  front_right.set_pins(Pinout::KNOB_FRONT_RIGHT);

  for (int i = 0; i < 4; i++) {
    knobs[i]->initialize();
    knobs[i]->set_calibration_value(0);
  }
}

void print_stuff(Knob const& knob, const char* name) {
  Serial.print("Knob '");
  Serial.print(name);
  Serial.print("' value: ");
  Serial.println(knob.read());
}

void loop() {
  print_stuff(top_left, "top left");
  print_stuff(top_right, "top right");
  print_stuff(front_left, "front left");
  print_stuff(front_right, "front right");

  delay(333);
}
