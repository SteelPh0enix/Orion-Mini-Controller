#include <Arduino.h>
#include <constants.hpp>
#include <pinout.hpp>

#include <joypad.hpp>

Joypad main_left, main_right, opt_left, opt_right;

void setup() {
  Serial.begin(SerialConstants::BaudRate);

  main_left.set_pins(Pinout::JOYPAD_PRIMARY_LEFT_X,
                     Pinout::JOYPAD_PRIMARY_LEFT_Y);
  main_right.set_pins(Pinout::JOYPAD_PRIMARY_RIGHT_X,
                      Pinout::JOYPAD_PRIMARY_RIGHT_Y);
  opt_left.set_pins(Pinout::JOYPAD_ADDITIONAL_LEFT_X,
                    Pinout::JOYPAD_ADDITIONAL_LEFT_Y);
  opt_right.set_pins(Pinout::JOYPAD_ADDITIONAL_RIGHT_X,
                     Pinout::JOYPAD_ADDITIONAL_RIGHT_Y);

  main_left.initialize();
  main_right.initialize();
  opt_left.initialize();
  opt_right.initialize();

  main_left.calibrate();
  main_right.calibrate();
  opt_left.calibrate();
  opt_right.calibrate();

  // For standarized input (X: left -, right +. Y: down -, up +):
  main_left.invert_x(false);
  main_left.invert_y(true);

  main_right.invert_x(true);
  main_right.invert_y(true);

  opt_left.invert_x(true);
  opt_left.invert_y(false);

  opt_right.invert_x(false);
  opt_right.invert_y(true);
}

void print_stuff(Joypad const& pad, const char* name) {
  auto data = pad.read();

  Serial.print("Joypad '");
  Serial.print(name);
  Serial.print("' X: ");
  Serial.print(data.x);
  Serial.print(", Y: ");
  Serial.println(data.y);
}

void loop() {
  print_stuff(main_left, "main left");
  print_stuff(main_right, "main right");
  print_stuff(opt_left, "opt left");
  print_stuff(opt_right, "opt right");
  Serial.println();

  delay(200);
}
