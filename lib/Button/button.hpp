#pragma once
#include <Arduino.h>
#include "../Module/module.hpp"

/*
  Class representing a simple button
*/

class Button : public ArduinoModule {
 public:
  // Constructors

  Button() = default;
  Button(unsigned button_pin, bool init = true, unsigned mode = INPUT_PULLUP);

  // Initialization functions

  virtual bool initialize() override;
  void set_pins(unsigned button_pin, unsigned mode = INPUT_PULLUP);

  // If you want to flip the readed state of button (for example, by default
  // digitalRead on button returns `0` when pressed, and you want to have `1`),
  // use this function to change behaviour of read() for this object.
  // It's `true` by default.
  void set_flip_state(bool state);

  // Read the state of button
  bool pressed() const;

  // Getters

  // Returns pin used by button
  unsigned pin() const;

  // Returns INPUT or INPUT_PULLUP
  unsigned input_mode() const;

  // Returns state of flip (if it negates readed value or not)
  bool flip_state() const;

  // This function executes a functor/lambda/anything callable with void(*)()
  // signature if button is pressed at the moment of calling, and then blocks
  // until button is un-pressed Note: If flip state is set that default button
  // state is ON, then it won't work properly. `sleep_time` is time which should
  // be waited before checking button state again when blocked. 10ms by default.
  template <typename F>
  void do_if_pressed(F function, unsigned sleep_time = 10) const {
    if (pressed()) {
      function();
      while (pressed()) {
        delay(sleep_time);
      }
    }
  }

  // This function executes a functor/lambda/anything callable with void(*)()
  // signature while button is pressed.
  // Same rules as above. `sleep_time` designates time between function calls.
  template <typename F>
  void do_while_pressed(F function, unsigned sleep_time = 10) const {
    while (pressed()) {
      function();
      delay(sleep_time);
    }
  }

 protected:
  bool m_flip_state{false};
  unsigned m_button_pin{};
  unsigned m_button_input_mode{INPUT_PULLUP};
};