#include "JsonDataParser.hpp"
#include "../../include/constants.hpp"
#include "../Controller/controller.hpp"

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
  auto right_switch_data =
      controller.get_switch(Controller::SwitchRight)->read();

  // Normalize the data properly
  int grasper_speed{0}, cramp_speed{0};

  switch (left_switch_data) {
    case Switch::State::Down:
      grasper_speed = -400;
      break;
    case Switch::State::Up:
      grasper_speed = 400;
      break;
    default:
      break;
  }

  switch (right_switch_data) {
    case Switch::State::Down:
      cramp_speed = -400;
      break;
    case Switch::State::Up:
      cramp_speed = 400;
      break;
    default:
      break;
  }

  // Normalize joypad data to -180 : 180
  left_joypad_data.y =
      constrain(map(left_joypad_data.y, JoypadMaxConstants::LeftMainJoypadDown,
                    JoypadMaxConstants::LeftMainJoypadUp, -180, 180),
                -180, 180);
  left_joypad_data.x =
      constrain(map(left_joypad_data.x, JoypadMaxConstants::LeftMainJoypadLeft,
                    JoypadMaxConstants::LeftMainJoypadRight, -180, 180),
                -180, 180);
  right_joypad_data.y = constrain(
      map(right_joypad_data.y, JoypadMaxConstants::RightMainJoypadDown,
          JoypadMaxConstants::RightMainJoypadUp, -180, 180),
      -180, 180);
  right_joypad_data.x = constrain(
      map(right_joypad_data.x, JoypadMaxConstants::RightMainJoypadLeft,
          JoypadMaxConstants::RightMainJoypadRight, -180, 180),
      -180, 180);

  // Put it in JSON
  json[JsonConstant::Speed] = left_joypad_data.y;
  json[JsonConstant::Turning] = left_joypad_data.x;
  json[JsonConstant::ArmTurntable] = right_joypad_data.x;
  json[JsonConstant::ArmShoulder] = right_joypad_data.y;
  json[JsonConstant::ArmForearm] = grasper_speed;
  json[JsonConstant::ArmCramp] = cramp_speed;

#ifdef DEBUG_JSON_PARSING
  Serial.print("Estimated JSON length: ");
  Serial.println(json.measureLength());
  json.printTo(Serial);
  Serial.println();
#endif

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

#ifdef DEBUG_JSON_PARSING
  Serial.print("Estimated JSON length: ");
  Serial.println(json.measureLength());
  json.printTo(Serial);
  Serial.println();
#endif

  json.printTo(buffer, BufferSize);
  m_buffer.clear();
}