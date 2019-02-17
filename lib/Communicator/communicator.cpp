#include "communicator.hpp"
#include <printf.h>
#include "../../include/constants.hpp"

void Communicator::initialize() {
  m_radio.begin();
  m_radio.setPALevel(RF24_PA_HIGH);
  m_radio.setDataRate(RF24_250KBPS);
  m_radio.setCRCLength(RF24_CRC_16);
  m_radio.openWritingPipe(RF24Constant::radio_address);
  m_radio.openReadingPipe(1, RF24Constant::rover_address);
  printf_begin();

  m_initialized = true;
}

bool Communicator::initialized() const { return m_initialized; }

void Communicator::send_data(char const* data, unsigned size) {
  if (!initialized()) return;

  m_radio.write(data, size);
}

void Communicator::print_debug_data() { m_radio.printDetails(); }