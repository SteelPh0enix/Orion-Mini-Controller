#include "analog_control.hpp"

AnalogControl::AnalogControl(unsigned pin, bool init) {
  set_pins(pin);
  if (init) initialize();
}

bool AnalogControl::initialize() {
  if (!pins_set()) return false;

  pinMode(m_pin, INPUT);
  m_initialized = true;
  return true;
}

void AnalogControl::set_pins(unsigned pin) {
  m_pin = pin;
  m_pins_set = true;
}

void AnalogControl::calibrate() { m_calibration = read_raw(); }

int AnalogControl::read_raw() const { return analogRead(m_pin); }

int AnalogControl::read() const { return normalize(read_raw()); }

int AnalogControl::normalize(int value) const { return value - m_calibration; }

unsigned AnalogControl::pin() const { return m_pin; }