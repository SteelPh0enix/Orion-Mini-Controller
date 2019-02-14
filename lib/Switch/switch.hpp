#pragma once
#include <Arduino.h>
#include "../Button/button.hpp"
#include "../Module/module.hpp"

/*
  Class for two-positional (up-off-down) switch
*/

class Switch : public ArduinoModule {
 public:
  enum class State { Up, Off, Down };

  Switch() = default;
  Switch(unsigned pin_down, unsigned pin_up, bool init = true,
         unsigned mode = INPUT_PULLUP);

  virtual bool initialize() override;
  void set_pins(unsigned pin_down, unsigned pin_up,
                unsigned mode = INPUT_PULLUP);

  State read() const;

  // See `Button` class for description
  void set_flip_state(bool state);
  bool flip_state() const;

  unsigned pin_up() const;
  unsigned pin_down() const;

  unsigned input_mode() const;

  using SwitchFunction = void (*)(State);

  // This function takes a functor/lambda/anything callable with void(*)(State)
  // signature when switch is in non-off state (state will be passed as argument
  // to functor). Similar to `Button::do_if_pressed`, check it out for detailed
  // description.
  void do_if_active(SwitchFunction function, unsigned sleep_time = 10);

  // Similar to above, but executes until switch goes back into off state
  void do_while_active(SwitchFunction function, unsigned sleep_time = 10);

 private:
  Button m_up{}, m_down{};
};