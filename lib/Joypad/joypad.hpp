#pragma once
#include <Arduino.h>
#include "../Module/module.hpp"

/*
  Joypad class
*/

class Joypad : public ArduinoModule {
 public:
  // Structures
  struct Data {
    int x, y;
  };

  // Constructors
  Joypad() = default;
  Joypad(unsigned x_axis, unsigned y_axis, bool init = true);

  // Initalization and calibration
  void set_pins(unsigned x_axis, unsigned y_axis);
  virtual bool initialize() override;

  // This function reads joypad value and sets it as `0` reference.
  // By default, it's half of ADC max value.
  void calibrate();

  // Those functions calibrate the axes
  void calibrate_x();
  void calibrate_y();

  // Same as above, but without normalization
  inline int x_axis_raw() const;
  inline int y_axis_raw() const;

  // Read and normalize data from X and Y axis
  inline int x_axis() const;
  inline int y_axis() const;

  // Read non-normalized data (straight analogRead)
  Data read_raw() const;

  // Read normalized data from joypad
  Data read() const;

 private:
  // `true` for X, `false` for Y
  // Internal usage only.
  inline int normalize_x(int value) const;
  inline int normalize_y(int value) const;

  unsigned m_x_axis{};
  unsigned m_y_axis{};

  int m_x_calibration{ADC_RESOLUTION_VALUE / 2};
  int m_y_calibration{ADC_RESOLUTION_VALUE / 2};
};
