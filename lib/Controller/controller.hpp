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

  static constexpr unsigned Button1{0};
  static constexpr unsigned Button2{1};
  static constexpr unsigned Button3{2};
  static constexpr unsigned Button4{3};
  static constexpr unsigned Button5{4};

  static constexpr unsigned JoyButtonLeft{5};
  static constexpr unsigned JoyButtonRight{6};

  static constexpr unsigned KnobTopLeft{0};
  static constexpr unsigned KnobTopRight{1};
  static constexpr unsigned KnobFrontLeft{2};
  static constexpr unsigned KnobFrontRight{3};

  static constexpr unsigned SwitchLeft{0};
  static constexpr unsigned SwitchRight{1};

  static constexpr unsigned JoypadMainLeft{0};
  static constexpr unsigned JoypadMainRight{1};
  static constexpr unsigned JoypadAddLeft{2};
  static constexpr unsigned JoypadAddRight{3};

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