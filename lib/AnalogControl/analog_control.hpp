#pragma once
#include <Arduino.h>
#include "../Module/module.hpp"

/*
  Class for abstract analog control module, with calibration
*/

class AnalogControl : public ArduinoModule {
 public:
  AnalogControl() = default;
  AnalogControl(unsigned pin, bool init = true);

  virtual bool initialize() override;
  void set_pins(unsigned pin);

  // This function calibrates the analog control according to actual state
  void calibrate();

  // This function allows to set custom calibration value
  void set_calibration_value(int value);

  int read_raw() const;
  int read() const;

  unsigned pin() const;

 protected:
  int normalize(int value) const;

  unsigned m_pin{};

  int m_calibration{0};
};