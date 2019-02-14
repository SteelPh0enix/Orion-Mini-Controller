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
  bool read() const;

  // Getters

  // Returns pin used by button
  unsigned pin() const;

  // Returns INPUT or INPUT_PULLUP
  unsigned input_mode() const;

  // Returns state of flip (if it negates readed value or not)
  bool flip_state() const;

 private:
  bool m_flip_state{true};
  unsigned m_button_pin{};
  unsigned m_button_input_mode{INPUT_PULLUP};
};