#include <iostream>

#include "../../src/bit.hpp"
#include "../../src/gameboy/gameboy.hpp"
#include "high-byte-dereference-test.hpp"
#include "../../src/gameboy/cpu/instructions/dereference-high-byte.hpp"
#include "../../src/gameboy/cpu/instructions/dereference-into-high-byte.hpp"

HighByteDereferenceTest::HighByteDereferenceTest():
  Test("High byte dereference instructions")
{
}

bool HighByteDereferenceTest::run() {
  Gameboy                 gameboy;
  DereferenceIntoHighByte into;
  DereferenceHighByte     to;

  uint8_t memoryValue;
  uint8_t registerValue;

  const uint8_t address  = 11;
  const uint8_t expected = 10;
  const uint8_t other    = 12;

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, expected);

  gameboy.mmu.write(address + 0xff00, other);

  into.execute(gameboy, &address);

  memoryValue   = gameboy.mmu[address + 0xff00];
  registerValue = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  if (memoryValue != registerValue || registerValue != expected) {
    std::cout << "The first half of the test failed" << std::endl;

    return false;
  }

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, other);
  gameboy.mmu.write(address + 0xff00, expected);

  to.execute(gameboy, &address);

  memoryValue   = gameboy.mmu[address + 0xff00];
  registerValue = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  if (memoryValue != registerValue || registerValue != expected) {
    std::cout << (unsigned int) registerValue << std::endl;
    std::cout << "The second half of the test failed" << std::endl;

    return false;
  }

  return true;
}
