#include "controller.hpp"
#include <Arduino.h>

#include "../../include/pinout.hpp"

namespace Index {
constexpr unsigned Button1{0};
constexpr unsigned Button2{1};
constexpr unsigned Button3{2};
constexpr unsigned Button4{3};
constexpr unsigned Button5{4};

constexpr unsigned JoyButtonLeft{5};
constexpr unsigned JoyButtonRight{6};

constexpr unsigned KnobTopLeft{0};
constexpr unsigned KnobTopRight{1};
constexpr unsigned KnobFrontLeft{2};
constexpr unsigned KnobFrontRight{3};

constexpr unsigned SwitchLeft{0};
constexpr unsigned SwitchRight{1};

constexpr unsigned JoypadMainLeft{0};
constexpr unsigned JoypadMainRight{1};
constexpr unsigned JoypadAddLeft{2};
constexpr unsigned JoypadAddRight{3};
}  // namespace Index

Controller::Controller() {
  // Pinout settings
  m_buttons[Index::Button1].set_pins(Pin::BUTTON_CONTROL_1);
  m_buttons[Index::Button2].set_pins(Pin::BUTTON_CONTROL_2);
  m_buttons[Index::Button3].set_pins(Pin::BUTTON_CONTROL_3);
  m_buttons[Index::Button4].set_pins(Pin::BUTTON_CONTROL_4);
  m_buttons[Index::Button5].set_pins(Pin::BUTTON_CONTROL_5);

  m_buttons[Index::JoyButtonLeft].set_pins(Pin::BUTTON_JOYPAD_LEFT);
  m_buttons[Index::JoyButtonRight].set_pins(Pin::BUTTON_JOYPAD_RIGHT);

  m_knobs[Index::KnobTopLeft].set_pins(Pin::KNOB_TOP_LEFT);
  m_knobs[Index::KnobTopRight].set_pins(Pin::KNOB_TOP_RIGHT);
  m_knobs[Index::KnobFrontLeft].set_pins(Pin::KNOB_FRONT_LEFT);
  m_knobs[Index::KnobFrontRight].set_pins(Pin::KNOB_FRONT_RIGHT);

  m_switches[Index::SwitchLeft].set_pins(Pin::TRIPOS_SWITCH_LEFT_DOWN,
                                         Pin::TRIPOS_SWITCH_LEFT_UP);
  m_switches[Index::SwitchRight].set_pins(Pin::TRIPOS_SWITCH_RIGHT_DOWN,
                                          Pin::TRIPOS_SWITCH_RIGHT_UP);

  m_joypads[Index::JoypadMainLeft].set_pins(Pin::JOYPAD_PRIMARY_LEFT_X,
                                            Pin::JOYPAD_PRIMARY_LEFT_Y);
  m_joypads[Index::JoypadMainRight].set_pins(Pin::JOYPAD_PRIMARY_RIGHT_X,
                                             Pin::JOYPAD_PRIMARY_RIGHT_Y);
  m_joypads[Index::JoypadAddLeft].set_pins(Pin::JOYPAD_ADDITIONAL_LEFT_X,
                                           Pin::JOYPAD_ADDITIONAL_LEFT_Y);
  m_joypads[Index::JoypadAddRight].set_pins(Pin::JOYPAD_ADDITIONAL_RIGHT_X,
                                            Pin::JOYPAD_ADDITIONAL_RIGHT_Y);

  // Configuration
  // Joypad input standarization

  m_joypads[Index::JoypadMainLeft].invert_x(false);
  m_joypads[Index::JoypadMainLeft].invert_y(true);

  m_joypads[Index::JoypadMainRight].invert_x(true);
  m_joypads[Index::JoypadMainRight].invert_y(true);

  m_joypads[Index::JoypadAddLeft].invert_x(true);
  m_joypads[Index::JoypadAddLeft].invert_y(false);

  m_joypads[Index::JoypadAddRight].invert_x(false);
  m_joypads[Index::JoypadAddRight].invert_y(true);
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

  calibrate();

  m_initialized = true;
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