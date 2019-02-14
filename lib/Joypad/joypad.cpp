#include "joypad.hpp"

Joypad::Joypad(unsigned x_axis, unsigned y_axis, bool init) {
  set_pins(x_axis, y_axis);
  if (init) initialize();
}

void Joypad::set_pins(unsigned x_axis, unsigned y_axis) {
  m_x_axis = x_axis;
  m_y_axis = y_axis;
  m_pins_set = true;
}

bool Joypad::initialize() {
  if (!pins_set()) return false;
  pinMode(m_x_axis, INPUT);
  pinMode(m_y_axis, INPUT);
  m_initialized = true;
  return true;
}

void Joypad::calibrate() {
  calibrate_x();
  calibrate_y();
}

void Joypad::calibrate_x() { m_x_calibration = analogRead(m_x_axis); }
void Joypad::calibrate_y() { m_y_calibration = analogRead(m_y_axis); }

inline int Joypad::x_axis_raw() const { return analogRead(m_x_axis); }
inline int Joypad::y_axis_raw() const { return analogRead(m_y_axis); }

inline int Joypad::x_axis() const { return normalize_x(x_axis_raw()); }
inline int Joypad::y_axis() const { return normalize_y(y_axis_raw()); }

Joypad::Data Joypad::read_raw() const { return {x_axis_raw(), y_axis_raw()}; }
Joypad::Data Joypad::read() const { return {x_axis(), y_axis()}; }

inline int Joypad::normalize_x(int value) const {
  return value - m_x_calibration;
}
inline int Joypad::normalize_y(int value) const {
  return value - m_y_calibration;
}