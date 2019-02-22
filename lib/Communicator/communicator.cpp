#include "communicator.hpp"
#include <printf.h>
#include "../../include/constants.hpp"

void Communicator::initialize() {
  m_radio.begin();
  m_radio.setAutoAck(1);
  m_radio.setPALevel(RF24_PA_HIGH);
  m_radio.setDataRate(RF24_2MBPS);
  m_radio.setCRCLength(RF24_CRC_16);
  m_radio.openWritingPipe(RF24Constant::radio_address);
  m_radio.openReadingPipe(1, RF24Constant::rover_address);
  printf_begin();

  m_initialized = true;
}

bool Communicator::initialized() const { return m_initialized; }

void Communicator::send_data(char const* data) {
  if (!initialized()) return;

  unsigned left_to_write{strlen(data)};
  unsigned bytes_to_write{};
  unsigned bytes_written{0};
  const unsigned payload_size = m_radio.getPayloadSize();

  while (left_to_write > 0) {
    if (left_to_write < payload_size) {
      bytes_to_write = left_to_write;
    } else {
      bytes_to_write = payload_size;
    }

    m_radio.write(data + bytes_written, bytes_to_write);
    left_to_write -= bytes_to_write;
    bytes_written += bytes_to_write;
  }
}

void Communicator::print_debug_data() { m_radio.printDetails(); }