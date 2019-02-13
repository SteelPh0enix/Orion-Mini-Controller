#include <Arduino.h>
#include <constants.hpp>

constexpr unsigned START_PIN{2};
constexpr unsigned END_PIN{53};
constexpr unsigned PIN_AMOUNT{END_PIN - START_PIN};
bool states[PIN_AMOUNT];

void setup() {
  memset(states, true, PIN_AMOUNT);
  Serial.begin(SerialConstants::BaudRate);
  for (int i{2}; i <= 53; i++) {
    pinMode(i, INPUT_PULLUP);
  }
}

void loop() {
  for (unsigned i{0}; i < PIN_AMOUNT; i++) {
    bool state = digitalRead(i);
    if (state != states[i]) {
      states[i] = state;
      Serial.print("Pin #");
      Serial.print(i + START_PIN);
      Serial.print(" state changed to ");
      Serial.println(!state);
    }
  }
  delay(100);
}