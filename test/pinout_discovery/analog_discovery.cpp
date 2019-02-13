#include <Arduino.h>
#include <constants.hpp>
#include <pinout.hpp>

constexpr unsigned START_PIN{A0};
constexpr unsigned END_PIN{A15};

constexpr unsigned NEXT_PIN_BUTTON{Pinout::TRIPOS_SWITCH_RIGHT_DOWN};
constexpr unsigned PREVIOUS_PIN_BUTTON{Pinout::TRIPOS_SWITCH_RIGHT_UP};

unsigned checked_pin{START_PIN};

void setup() {
  // Init serial
  Serial.begin(SerialConstants::BaudRate);

  // Set up pins
  for (unsigned i{START_PIN}; i <= END_PIN; i++) {
    pinMode(i, INPUT);
  }

  pinMode(NEXT_PIN_BUTTON, INPUT_PULLUP);
  pinMode(PREVIOUS_PIN_BUTTON, INPUT_PULLUP);
}

template <typename F>
void do_if_clicked(unsigned button, F function) {
  if (digitalRead(button)) {
    function();
    while (digitalRead(button)) {
      delay(10);
    }
  }
}

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
  delay(100);
}