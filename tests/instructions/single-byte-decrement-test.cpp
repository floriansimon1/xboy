#include <iostream>

#include "../../src/gameboy/cpu/instructions/single-byte-increment.hpp"
#include "single-byte-decrement-test.hpp"
#include "../../src/gameboy/gameboy.hpp"

SingleByteDecrementTest::SingleByteDecrementTest():
  Test("Single-byte decrement instruction")
{
}

bool SingleByteDecrementTest::run() {
  Gameboy             gameboy;
  SingleByteIncrement instruction(&Cpu::bc, true, -1);

  for (auto i = 0; i < 16; i++) {
    gameboy.cpu.bc = i * 16 + 1;
    gameboy.cpu.af = 0;

    instruction.execute(gameboy, NULL);

    const bool expectZeroFlag = !i;

    if (
      gameboy.cpu.bc != i * 16
      || !gameboy.cpu.getSubtractFlag()
      || gameboy.cpu.getHalfCarryFlag()
      || (gameboy.cpu.getZeroFlag() != expectZeroFlag)
    ) {
      std::cout << "No half-carry #" << i << '\n'
                << "Flags: " << (unsigned int) gameboy.cpu.af << '\n'
                << "Value: " << gameboy.cpu.bc << std::endl;

      return false;
    }

    gameboy.cpu.af = 0;

    instruction.execute(gameboy, NULL);

    if (
      gameboy.cpu.getZeroFlag()
      || !gameboy.cpu.getSubtractFlag()
      || !gameboy.cpu.getHalfCarryFlag()
      || gameboy.cpu.bc != (i == 0 ? 255 : i * 16 - 1)
    ) {
      std::cout << "Half-carry #" << i << '\n'
                << "Flags: " << (unsigned int) gameboy.cpu.af << '\n'
                << "Value: " << gameboy.cpu.bc << std::endl;

      return false;
    }
  }

  return true;
}
