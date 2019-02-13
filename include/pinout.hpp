// File with pinout for the controller
#pragma once
#include <stdint.h>

// Pinout constants
// Naming convention: TYPE_POSITION_[INFO]
// TYPE - type of control, for example BUTTON or TRIPOS_SWITCH
// POSITION - position in remote (or role of control)
// INFO - additional information, optional
namespace Pinout {
// 5 front clicky control buttons. Counting from left to right.
constexpr unsigned BUTTON_CONTROL_1{27};
constexpr unsigned BUTTON_CONTROL_2{26};
constexpr unsigned BUTTON_CONTROL_3{25};
constexpr unsigned BUTTON_CONTROL_4{24};
constexpr unsigned BUTTON_CONTROL_5{23};

// Top tri-positional switches
constexpr unsigned TRIPOS_SWITCH_LEFT_DOWN{33};
constexpr unsigned TRIPOS_SWITCH_LEFT_UP{32};
constexpr unsigned TRIPOS_SWITCH_RIGHT_DOWN{31};
constexpr unsigned TRIPOS_SWITCH_RIGHT_UP{30};

// Joypad buttons. Those are odd, because when set as INPUT_PULLUP, they return
// 0 when pressed, in opposite to the rest of buttons
constexpr unsigned BUTTON_JOYPAD_LEFT{28};
constexpr unsigned BUTTON_JOYPAD_RIGHT{29};

// Analog knobs - clockwise rotation increases value
constexpr unsigned KNOB_TOP_LEFT{A0};
constexpr unsigned KNOB_TOP_RIGHT{A3};
constexpr unsigned KNOB_FRONT_LEFT{A1};
constexpr unsigned KNOB_FRONT_RIGHT{A2};

// Joypads with descriptions of returned values

// Going right increases value
constexpr unsigned JOYPAD_PRIMARY_LEFT_X{A5};
// Going up decreases value
constexpr unsigned JOYPAD_PRIMARY_LEFT_Y{A4};

// Going right decreases value
constexpr unsigned JOYPAD_PRIMARY_RIGHT_X{A7};
// Going up decreases value
constexpr unsigned JOYPAD_PRIMARY_RIGHT_Y{A6};

// Going right decreases value
constexpr unsigned JOYPAD_ADDITIONAL_LEFT_X{};
// Going up increases value
constexpr unsigned JOYPAD_ADDITIONAL_LEFT_Y{};

// Going right increases value
constexpr unsigned JOYPAD_ADDITIONAL_RIGHT_X{};
// Going up decreases value
constexpr unsigned JOYPAD_ADDITIONAL_RIGHT_Y{};
}  // namespace Pinout