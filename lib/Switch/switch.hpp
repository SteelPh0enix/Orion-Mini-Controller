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

 private:
  Button m_up{}, m_down{};
};