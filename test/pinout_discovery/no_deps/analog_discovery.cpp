/*
  Simple analog, dependency-free, configurable pin discoverer.

  Author: Wojciech Olech (https://gitlab.com/SteelPh0enix/)
*/

#include <Arduino.h>

// === Configuration ===

constexpr unsigned NEXT_PIN_BUTTON{
    3 /* CHANGE THE VALUE TO BUTTON PIN OR LEAVE AS-IS */};
constexpr unsigned PREVIOUS_PIN_BUTTON{
    3
    /* CHANGE THE VALUE TO BUTTON PIN OR LEAVE AS-IS */};

// Change this if you want to shrink checked pins range.
// Change `START_PIN` to pin you'll want to check if you don't have any buttons,
// since program will start from it
constexpr unsigned START_PIN{A0};
constexpr unsigned END_PIN{A15};

constexpr unsigned long SERIAL_BAUD_RATE{9600};
constexpr unsigned long SLEEP_TIME{100};

// === End of configuration ===

unsigned checked_pin{START_PIN};

void setup() {
  // Init serial
  Serial.begin(SERIAL_BAUD_RATE);

  // Set up pins
  for (unsigned i{START_PIN}; i <= END_PIN; i++) {
    pinMode(i, INPUT);
  }

  pinMode(NEXT_PIN_BUTTON, INPUT_PULLUP);
  pinMode(PREVIOUS_PIN_BUTTON, INPUT_PULLUP);

  Serial.print("Starting discovery on A");
  Serial.println(checked_pin - START_PIN);
  delay(500);
}

// Boilerplate for button callback
template <typename F>
void do_if_clicked(unsigned button, F function) {
  if (digitalRead(button)) {
    function();
    while (digitalRead(button)) {
      delay(10);
    }
  }
}

// Boilerplate for pin state change
void print_pin_changed(unsigned pin) {
  Serial.print("Changed pin to A");
  Serial.println(pin - START_PIN);
}

void loop() {
  do_if_clicked(NEXT_PIN_BUTTON, [&]() {
    checked_pin++;
    if (checked_pin > END_PIN) checked_pin = START_PIN;

    print_pin_changed(checked_pin);
  });

  do_if_clicked(PREVIOUS_PIN_BUTTON, [&]() {
    checked_pin--;
    if (checked_pin < START_PIN) checked_pin = END_PIN;

    print_pin_changed(checked_pin);
  });

  Serial.println(analogRead(checked_pin));
  delay(SLEEP_TIME);
}