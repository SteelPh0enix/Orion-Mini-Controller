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
constexpr const char* Speed{"SPD"};
constexpr const char* Turning{"TRN"};
constexpr const char* ArmRotation{"AROT"};
constexpr const char* ArmElbow{"AELB"};
constexpr const char* ArmGrasper{"AGRP"};
constexpr const char* ArmCramp{"ACRP"};
}  // namespace JsonConstant

enum class Command { None, Stop };

namespace RF24Constant {
constexpr unsigned char RadioAddress[6]{"AROVR"};
constexpr unsigned char RoverAddress[6]{"ZROVR"};
constexpr unsigned PayloadSize{32};
}  // namespace RF24Constant