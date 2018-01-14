#include <iostream>

#include "../../gameboy.hpp"
#include "write-two-bytes-register-to-address-test.hpp"
#include "../../cpu/instructions/write-two-bytes-register-to-address.hpp"

WriteTwoBytesRegisterToAddressTest::WriteTwoBytesRegisterToAddressTest():
  Test("Write 2-bytes register to address instruction")
{
}

bool WriteTwoBytesRegisterToAddressTest::run() {
  Gameboy                        gameboy;
  WriteTwoBytesRegisterToAddress instruction(&Cpu::sp);

  const auto value = 143;

  gameboy.cpu.sp = value;

  const uint8_t lowByte  = 100;
  const uint8_t highByte = 0;

  uint16_t data = (highByte << 8) | lowByte;

  instruction.execute(gameboy, reinterpret_cast<uint8_t*>(&data));

  const auto result = *reinterpret_cast<uint16_t*>(gameboy.mmu.memory + 100);

  const bool success = result == value;

  if (!success) {
    std::cout << "Value: " << (unsigned int) result << std::endl;
  }

  return success;
}

