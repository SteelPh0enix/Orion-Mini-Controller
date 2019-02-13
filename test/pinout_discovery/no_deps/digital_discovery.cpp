/*
  Simple digital, dependency-free, configurable pin discoverer.

  Author: Wojciech Olech (https://gitlab.com/SteelPh0enix/)
*/

#include <Arduino.h>

// === Configuration ===

// Constants for scanning. Change if you'll want to shrink range of checked pins
constexpr unsigned DIGITAL_PIN_START{2};
constexpr unsigned DIGITAL_PIN_END{53};

constexpr unsigned long SERIAL_BAUD_RATE{9600};
constexpr unsigned long SLEEP_TIME{100};

// === End of configuration ===

constexpr unsigned DIGITAL_PIN_AMOUNT{DIGITAL_PIN_END - DIGITAL_PIN_START};

// Data arrays
bool digital_states[DIGITAL_PIN_AMOUNT];

void setup() {
  // Init memory
  memset(digital_states, true, DIGITAL_PIN_AMOUNT * sizeof(bool));

  // Init serial
  Serial.begin(SERIAL_BAUD_RATE);

  // Init pins
  for (unsigned i{DIGITAL_PIN_START}; i <= DIGITAL_PIN_END; i++) {
    pinMode(i, INPUT_PULLUP);
  }
}

void loop() {
  // Check the analog and digital states periodically every 100ms
  for (unsigned i{0}; i < DIGITAL_PIN_AMOUNT; i++) {
    bool state = digitalRead(i + DIGITAL_PIN_START);
    if (state != digital_states[i]) {
      digital_states[i] = state;
      Serial.print("Pin #");
      Serial.print(i + DIGITAL_PIN_START);
      Serial.print(": digital state changed to ");
      Serial.println(state);
    }
  }
  delay(SLEEP_TIME);
}