#include <Arduino.h>
#include <constants.hpp>

// Constants for scanning
constexpr unsigned DIGITAL_PIN_START{2};
constexpr unsigned DIGITAL_PIN_END{53};
constexpr unsigned DIGITAL_PIN_AMOUNT{DIGITAL_PIN_END - DIGITAL_PIN_START};

// Data arrays
bool digital_states[DIGITAL_PIN_AMOUNT];

void setup() {
  // Init memory
  memset(digital_states, true, DIGITAL_PIN_AMOUNT * sizeof(bool));

  // Init serial
  Serial.begin(SerialConstants::BaudRate);

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
      Serial.println(!state);
    }
  }
  delay(100);
}