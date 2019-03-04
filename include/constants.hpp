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

namespace NormalizationConstant {
constexpr int MaxNormalizedValue{180};
constexpr int MinNormalizedValue{-180};
}  // namespace NormalizationConstant

namespace JoypadMaxConstant {
constexpr int LeftMainJoypadUp{355};
constexpr int LeftMainJoypadDown{-355};
constexpr int LeftMainJoypadLeft{-360};
constexpr int LeftMainJoypadRight{360};

constexpr int RightMainJoypadUp{355};
constexpr int RightMainJoypadDown{-355};
constexpr int RightMainJoypadLeft{-360};
constexpr int RightMainJoypadRight{360};

// TBD: not needed now
constexpr int LeftAdditionalJoypadUp{500};
constexpr int LeftAdditionalJoypadDown{-500};
constexpr int LeftAdditionalJoypadLeft{-500};
constexpr int LeftAdditionalJoypadRight{500};

constexpr int RightAdditionalJoypadUp{500};
constexpr int RightAdditionalJoypadDown{-500};
constexpr int RightAdditionalJoypadLeft{-500};
constexpr int RightAdditionalJoypadRight{500};

}  // namespace JoypadMaxConstant