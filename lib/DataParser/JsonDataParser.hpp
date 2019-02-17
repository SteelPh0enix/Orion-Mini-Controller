#pragma once
#include <ArduinoJson.hpp>
#include "DataParser.hpp"

/*
  Class parsing data from Controller to JSON byte array
*/

class JsonDataParser : public DataParser {
 public:
  constexpr static unsigned BufferSize{128};

  virtual void parse_movement(Controller const& controller,
                              char* buffer) override;
  virtual void parse_command(Command command, char* buffer) override;

 private:
  ArduinoJson::StaticJsonBuffer<BufferSize> m_buffer{};
};