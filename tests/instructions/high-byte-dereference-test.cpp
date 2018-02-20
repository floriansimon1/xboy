#include <iostream>

#include "../../src/gameboy.hpp"
#include "high-byte-dereference-test.hpp"
#include "../../src/cpu/instructions/dereference-high-byte.hpp"
#include "../../src/cpu/instructions/dereference-into-high-byte.hpp"

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
  gameboy.mmu.memory[0xff00 + address] = other;

  into.execute(gameboy, &address);

  memoryValue   = gameboy.mmu.memory[0xff00 + address];
  registerValue = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  if (memoryValue != registerValue || registerValue != expected) {
    std::cout << "The first half of the test failed" << std::endl;

    return false;
  }

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, other);
  gameboy.mmu.memory[0xff00 + address] = expected;

  to.execute(gameboy, &address);

  memoryValue   = gameboy.mmu.memory[0xff00 + address];
  registerValue = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  if (memoryValue != registerValue || registerValue != expected) {
    std::cout << "The second half of the test failed" << std::endl;

    return false;
  }

  return true;
}
