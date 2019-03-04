#include "JsonDataParser.hpp"
#include "../../include/constants.hpp"
#include "../Controller/controller.hpp"

inline int normalize_value(int value, int min, int max) {
  return constrain(
      map(value, min, max, NormalizationConstant::MinNormalizedValue,
          NormalizationConstant::MaxNormalizedValue),
      NormalizationConstant::MinNormalizedValue,
      NormalizationConstant::MaxNormalizedValue);
}

void JsonDataParser::parse_movement(Controller const& controller,
                                    char* buffer) {
  if (!controller.initialized()) return;

  // Create JSON object
  auto& json = m_buffer.createObject();

  // Read the data from controller
  auto left_joypad_data =
      controller.get_joypad(Controller::JoypadMainLeft)->read();
  auto right_joypad_data =
      controller.get_joypad(Controller::JoypadMainRight)->read();
  auto left_switch_data = controller.get_switch(Controller::SwitchLeft)->read();
  auto right_additional_pad_data =
      controller.get_joypad(Controller::JoypadAddRight)->read();

  // Normalize the data properly
  int cramp_speed{0};

  switch (left_switch_data) {
    case Switch::State::Down:
      cramp_speed = NormalizationConstant::MinNormalizedValue;
      break;
    case Switch::State::Up:
      cramp_speed = NormalizationConstant::MaxNormalizedValue;
      break;
    default:
      break;
  }

  // Normalize joypad data to NormalizationConstant::MinNormalizedValue :
  // NormalizationConstant::MaxNormalizedValue
  left_joypad_data.y =
      normalize_value(left_joypad_data.y, JoypadMaxConstant::LeftMainJoypadDown,
                      JoypadMaxConstant::LeftMainJoypadUp);
  left_joypad_data.x =
      normalize_value(left_joypad_data.x, JoypadMaxConstant::LeftMainJoypadLeft,
                      JoypadMaxConstant::LeftMainJoypadRight);

  right_joypad_data.y = normalize_value(right_joypad_data.y,
                                        JoypadMaxConstant::RightMainJoypadDown,
                                        JoypadMaxConstant::RightMainJoypadUp);
  right_joypad_data.x = normalize_value(
      right_joypad_data.x, JoypadMaxConstant::RightMainJoypadLeft,
      JoypadMaxConstant::RightMainJoypadRight);

  right_additional_pad_data.x = normalize_value(
      right_additional_pad_data.x, JoypadMaxConstant::RightAdditionalJoypadLeft,
      JoypadMaxConstant::RightAdditionalJoypadRight);
  right_additional_pad_data.y = normalize_value(
      right_additional_pad_data.y, JoypadMaxConstant::RightAdditionalJoypadDown,
      JoypadMaxConstant::RightAdditionalJoypadUp);

  // Put it in JSON
  json[JsonConstant::Speed] = right_joypad_data.y;
  json[JsonConstant::Turning] = right_joypad_data.x;
  json[JsonConstant::ArmTurntable] = left_joypad_data.x;
  json[JsonConstant::ArmShoulder] = left_joypad_data.y;
  json[JsonConstant::ArmForearm] = right_additional_pad_data.x;
  json[JsonConstant::ArmWrist] = right_additional_pad_data.y;
  json[JsonConstant::ArmCramp] = cramp_speed;

  // Parse to byte array
  json.printTo(buffer, BufferSize);

  // Clear bufffer
  m_buffer.clear();
}

void JsonDataParser::parse_command(Command command, char* buffer) {
  auto& json = m_buffer.createObject();

  switch (command) {
    case Command::Stop:
      // Put it in JSON
      json[JsonConstant::Speed] = 0;
      json[JsonConstant::Turning] = 0;
      json[JsonConstant::ArmTurntable] = 0;
      json[JsonConstant::ArmShoulder] = 0;
      json[JsonConstant::ArmForearm] = 0;
      json[JsonConstant::ArmCramp] = 0;

    case Command::None:
      break;
  }

  json.printTo(buffer, BufferSize);
  m_buffer.clear();
}