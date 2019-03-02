// Various constants used in program, shared with rover
#pragma once

// Debug macros
// #define DEBUG_JSON_PARSING

// Namespace for serial port constants
namespace SerialConstant {
constexpr bool EnabledByDefault{false};
constexpr unsigned long BaudRate{128000};
}  // namespace SerialConstant

// Namespace for JSON constants
namespace JsonConstant {
constexpr char const* Speed{"CSPD"};
constexpr char const* Turning{"CTRN"};
constexpr char const* ArmTurntable{"ATRN"};
constexpr char const* ArmShoulder{"ASHL"};
constexpr char const* ArmForearm{"AFRA"};
constexpr char const* ArmWrist{"AWRS"};
constexpr char const* ArmCramp{"ACRP"};
}  // namespace JsonConstant

enum class Command { None, Stop };

namespace RF24Constant {
constexpr unsigned char RadioAddress[6]{"AROVR"};
constexpr unsigned char RoverAddress[6]{"ZROVR"};
constexpr unsigned PayloadSize{32};
constexpr unsigned Channel{100};
}  // namespace RF24Constant

namespace JoypadMaxConstants {
constexpr int LeftMainJoypadUp{355};
constexpr int LeftMainJoypadDown{-355};
constexpr int LeftMainJoypadLeft{-360};
constexpr int LeftMainJoypadRight{360};

constexpr int RightMainJoypadUp{355};
constexpr int RightMainJoypadDown{-355};
constexpr int RightMainJoypadLeft{-360};
constexpr int RightMainJoypadRight{360};

// TBD: not needed now
constexpr int LeftAdditionalJoypadUp{};
constexpr int LeftAdditionalJoypadDown{};
constexpr int LeftAdditionalJoypadLeft{};
constexpr int LeftAdditionalJoypadRight{};

constexpr int RightAdditionalJoypadUp{};
constexpr int RightAdditionalJoypadDown{};
constexpr int RightAdditionalJoypadLeft{};
constexpr int RightAdditionalJoypadRight{};

}  // namespace JoypadMaxConstants