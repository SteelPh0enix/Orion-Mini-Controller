// Various constants used in program
#pragma once

// Namespace for serial port constants
namespace SerialConstants {
constexpr bool EnabledByDefault{true};
constexpr unsigned long BaudRate{128000};
}  // namespace SerialConstants

// Namespace for JSON constants
namespace JsonConstants {
constexpr const char* Speed{"SPD"};
constexpr const char* Turning{"TRN"};
constexpr const char* ArmRotation{"AROT"};
constexpr const char* ArmElbow{"AELB"};
constexpr const char* ArmGrasper{"AGRP"};
constexpr const char* ArmCramp{"ACRP"};
}  // namespace JsonConstants