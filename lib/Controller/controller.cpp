#include "controller.hpp"
#include <Arduino.h>

#include "../../include/pinout.hpp"

Controller::Controller() {
  // Pinout settings
  m_buttons[Button1].set_pins(Pin::BUTTON_CONTROL_1);
  m_buttons[Button2].set_pins(Pin::BUTTON_CONTROL_2);
  m_buttons[Button3].set_pins(Pin::BUTTON_CONTROL_3);
  m_buttons[Button4].set_pins(Pin::BUTTON_CONTROL_4);
  m_buttons[Button5].set_pins(Pin::BUTTON_CONTROL_5);

  m_buttons[JoyButtonLeft].set_pins(Pin::BUTTON_JOYPAD_LEFT);
  m_buttons[JoyButtonRight].set_pins(Pin::BUTTON_JOYPAD_RIGHT);

  m_knobs[KnobTopLeft].set_pins(Pin::KNOB_TOP_LEFT);
  m_knobs[KnobTopRight].set_pins(Pin::KNOB_TOP_RIGHT);
  m_knobs[KnobFrontLeft].set_pins(Pin::KNOB_FRONT_LEFT);
  m_knobs[KnobFrontRight].set_pins(Pin::KNOB_FRONT_RIGHT);

  m_switches[SwitchLeft].set_pins(Pin::TRIPOS_SWITCH_LEFT_DOWN,
                                  Pin::TRIPOS_SWITCH_LEFT_UP);
  m_switches[SwitchRight].set_pins(Pin::TRIPOS_SWITCH_RIGHT_DOWN,
                                   Pin::TRIPOS_SWITCH_RIGHT_UP);

  m_joypads[JoypadMainLeft].set_pins(Pin::JOYPAD_PRIMARY_LEFT_X,
                                     Pin::JOYPAD_PRIMARY_LEFT_Y);
  m_joypads[JoypadMainRight].set_pins(Pin::JOYPAD_PRIMARY_RIGHT_X,
                                      Pin::JOYPAD_PRIMARY_RIGHT_Y);
  m_joypads[JoypadAddLeft].set_pins(Pin::JOYPAD_ADDITIONAL_LEFT_X,
                                    Pin::JOYPAD_ADDITIONAL_LEFT_Y);
  m_joypads[JoypadAddRight].set_pins(Pin::JOYPAD_ADDITIONAL_RIGHT_X,
                                     Pin::JOYPAD_ADDITIONAL_RIGHT_Y);

  // Configuration
  // Joypad input standarization

  m_joypads[JoypadMainLeft].invert_x(false);
  m_joypads[JoypadMainLeft].invert_y(true);

  m_joypads[JoypadMainRight].invert_x(true);
  m_joypads[JoypadMainRight].invert_y(true);

  m_joypads[JoypadAddLeft].invert_x(true);
  m_joypads[JoypadAddLeft].invert_y(false);

  m_joypads[JoypadAddRight].invert_x(false);
  m_joypads[JoypadAddRight].invert_y(true);
}

void Controller::initialize() {
  for (unsigned i{0}; i < ButtonCount; i++) {
    m_buttons[i].initialize();
  }

  for (unsigned i{0}; i < KnobCount; i++) {
    m_knobs[i].initialize();
  }

  for (unsigned i{0}; i < SwitchCount; i++) {
    m_switches[i].initialize();
  }

  for (unsigned i{0}; i < JoypadCount; i++) {
    m_joypads[i].initialize();
  }

  m_initialized = true;

  calibrate();
}

bool Controller::initialized() const { return m_initialized; }

void Controller::calibrate() {
  if (!initialized()) return;

  for (unsigned i{0}; i < JoypadCount; i++) {
    m_joypads[i].calibrate();
  }
}

Button const* Controller::get_button(unsigned index) const {
  if (index < ButtonCount && initialized()) {
    return &(m_buttons[index]);
  }

  return nullptr;
}

Knob const* Controller::get_knob(unsigned index) const {
  if (index < KnobCount && initialized()) {
    return &(m_knobs[index]);
  }

  return nullptr;
}

Switch const* Controller::get_switch(unsigned index) const {
  if (index < SwitchCount && initialized()) {
    return &(m_switches[index]);
  }

  return nullptr;
}

Joypad const* Controller::get_joypad(unsigned index) const {
  if (index < JoypadCount && initialized()) {
    return &(m_joypads[index]);
  }

  return nullptr;
}