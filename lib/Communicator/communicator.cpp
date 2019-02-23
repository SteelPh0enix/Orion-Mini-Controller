#include "communicator.hpp"
#include <printf.h>
#include "../../include/constants.hpp"

void Communicator::initialize() {
  m_radio.begin();
  m_radio.setAutoAck(1);
  m_radio.setPayloadSize(RF24Constant::PayloadSize);
  m_radio.setPALevel(RF24_PA_MAX);
  m_radio.setDataRate(RF24_250KBPS);
  m_radio.setCRCLength(RF24_CRC_16);
  m_radio.openWritingPipe(RF24Constant::RadioAddress);
  m_radio.openReadingPipe(1, RF24Constant::RoverAddress);
  printf_begin();

  m_initialized = true;
}

bool Communicator::initialized() const { return m_initialized; }

void Communicator::send_data(char const* data) {
  if (!initialized()) return;

  unsigned left_to_write{strlen(data)};
  unsigned bytes_to_write{};
  unsigned bytes_written{0};

  while (left_to_write > 0) {
    if (left_to_write < RF24Constant::PayloadSize) {
      bytes_to_write = left_to_write;
    } else {
      bytes_to_write = RF24Constant::PayloadSize;
    }

    m_radio.write(data + bytes_written, bytes_to_write);
    left_to_write -= bytes_to_write;
    bytes_written += bytes_to_write;
  }
}

void Communicator::print_debug_data() { m_radio.printDetails(); }