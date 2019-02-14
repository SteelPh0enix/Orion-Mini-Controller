#include "button.hpp"

Button::Button(unsigned button_pin, unsigned mode, bool init) {
  set_pins(button_pin, mode);
  if (init) initialize();
}

bool Button::initialize() {
  if (!pins_set()) return false;
  if (initialized()) return true;

  pinMode(m_button_pin, m_button_input_state);
  m_initialized = true;
  return true;
}

void Button::set_pins(unsigned button_pin, unsigned mode) {
  m_button_pin = button_pin;
  m_button_input_state = mode;
  m_pins_set = true;
}

void Button::set_flip_state(bool state) { m_flip_state = state; }

bool Button::read() const {
  bool state = digitalRead(m_button_pin);
  return (m_flip_state ? !state : state);
}

unsigned Button::pin() const { return m_button_pin; }
unsigned Button::input_state() const { return m_button_input_state; }
bool Button::flip_state() const { return m_flip_state; }