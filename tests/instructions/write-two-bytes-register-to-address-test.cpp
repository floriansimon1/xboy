#include <iostream>

#include "../../src/gameboy/gameboy.hpp"
#include "write-two-bytes-register-to-address-test.hpp"
#include "../../src/gameboy/cpu/instructions/write-two-bytes-register-to-address.hpp"

WriteTwoBytesRegisterToAddressTest::WriteTwoBytesRegisterToAddressTest():
  Test("Write word register to address instruction")
{
}

bool WriteTwoBytesRegisterToAddressTest::run() {
  Gameboy                        gameboy;
  WriteTwoBytesRegisterToAddress instruction(&Cpu::sp);

  const uint16_t value   = 143;
  const uint16_t address = Mmu::ramStart;

  gameboy.cpu.sp = value;

  instruction.execute(gameboy, reinterpret_cast<const uint8_t*>(&address));

  const auto result = gameboy.mmu.readWord(address);

  if (result != value) {
    std::cout << "Value: " << (unsigned int) result << std::endl;

    return false;
  }

  return true;
}
