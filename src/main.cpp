#include <Arduino.h>
#include <constants.hpp>
#include <pinout.hpp>

#include <button.hpp>

Button buttons[5];

void setup() {
  buttons[0] = Button(Pinout::BUTTON_CONTROL_1);
  buttons[1] = Button(Pinout::BUTTON_CONTROL_2);
  buttons[2] = Button(Pinout::BUTTON_CONTROL_3);
  buttons[3] = Button(Pinout::BUTTON_CONTROL_4);
  buttons[4] = Button(Pinout::BUTTON_CONTROL_5);

  for (unsigned i{0}; i < 5; i++) {
    buttons[i].set_flip_state(false);
  }

  Serial.begin(SerialConstants::BaudRate);
}

void loop() {
  for (unsigned i{0}; i < 5; i++) {
    buttons[i].do_if_pressed([&]() {
      Serial.print("Button #");
      Serial.print(i + 1);
      Serial.print(" state is ");
      Serial.println(buttons[i].read() ? "ON" : "OFF");
    });
  }

  Serial.println();
  delay(500);
}
