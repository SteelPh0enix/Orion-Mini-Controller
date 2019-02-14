#include "switch.hpp"

Switch::Switch(unsigned pin_down, unsigned pin_up, bool init, unsigned mode) {
  set_pins(pin_down, pin_up, mode);
  if (init) initialize();
}

bool Switch::initialize() {
  if (!pins_set()) return false;
  m_up.initialize();
  m_down.initialize();
  m_initialized = true;
  return true;
}

void Switch::set_pins(unsigned pin_down, unsigned pin_up, unsigned mode) {
  m_up.set_pins(pin_up, mode);
  m_down.set_pins(pin_down, mode);
  m_pins_set = true;
}

Switch::State Switch::read() const {
  if (m_up.read()) return Switch::State::Up;
  if (m_down.read()) return Switch::State::Down;
  return Switch::State::Off;
}

void Switch::set_flip_state(bool state) {
  m_up.set_flip_state(state);
  m_down.set_flip_state(state);
}
bool Switch::flip_state() const { return m_up.flip_state(); }

unsigned Switch::pin_up() const { return m_up.pin(); }
unsigned Switch::pin_down() const { return m_down.pin(); }

unsigned Switch::input_mode() const { return m_up.input_mode(); }

void Switch::do_if_active(Switch::SwitchFunction function,
                          unsigned sleep_time = 10) {
  auto state = read();
  if (state != Switch::State::Off) {
    function(state);
    while (read() != Switch::State::Off) {
      delay(sleep_time);
    }
  }
}

void Switch::do_while_active(Switch::SwitchFunction function,
                             unsigned sleep_time = 10) {
  Switch::State state;
  while ((state = read()) != Switch::State::Off) {
    function(state);
    delay(sleep_time);
  }
}
