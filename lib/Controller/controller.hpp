#pragma once
#include <button.hpp>
#include <joypad.hpp>
#include <knob.hpp>
#include <switch.hpp>

/*
  Main class of the remote controller
*/

class Controller {
 public:
  static constexpr unsigned ButtonCount{7};
  static constexpr unsigned KnobCount{4};
  static constexpr unsigned SwitchCount{2};
  static constexpr unsigned JoypadCount{4};

  Controller();
  void initialize();
  bool initialized() const;

  void calibrate();

  Button const* get_button(unsigned index) const;
  Knob const* get_knob(unsigned index) const;
  Switch const* get_switch(unsigned index) const;
  Joypad const* get_joypad(unsigned index) const;

 private:
  bool m_initialized{false};

  Button m_buttons[ButtonCount];
  Knob m_knobs[KnobCount];
  Switch m_switches[SwitchCount];
  Joypad m_joypads[JoypadCount];
};