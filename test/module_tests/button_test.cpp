#include <Arduino.h>
#include <constants.hpp>
#include <pinout.hpp>

#include <button.hpp>

Button buttons[5];

void setup() {
  buttons[0] = Button(Pin::BUTTON_CONTROL_1);
  buttons[1] = Button(Pin::BUTTON_CONTROL_2);
  buttons[2] = Button(Pin::BUTTON_CONTROL_3);
  buttons[3] = Button(Pin::BUTTON_CONTROL_4);
  buttons[4] = Button(Pin::BUTTON_CONTROL_5);

  Serial.begin(SerialConstants::BaudRate);
}

void loop() {
  for (unsigned i{0}; i < 5; i++) {
    buttons[i].do_while_pressed([&]() {
      Serial.print("Button #");
      Serial.print(i + 1);
      Serial.print(" state is ");
      Serial.println(buttons[i].read() ? "ON" : "OFF");
    });
  }

  delay(50);
}
