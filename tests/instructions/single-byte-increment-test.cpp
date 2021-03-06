#include <iostream>

#include "../../src/gameboy/cpu/instructions/single-byte-increment.hpp"
#include "single-byte-increment-test.hpp"
#include "../../src/gameboy/gameboy.hpp"

SingleByteIncrementTest::SingleByteIncrementTest():
  Test("Single-byte increment instruction")
{
}

bool SingleByteIncrementTest::run() {
  Gameboy             gameboy;
  SingleByteIncrement instruction(&Cpu::bc, true, 1);

  for (auto i = 1; i <= 16; i++) {
    gameboy.cpu.bc = i * 16 - 2;
    gameboy.cpu.af = 0;

    instruction.execute(gameboy, NULL);

    if (
      gameboy.cpu.getZeroFlag()
      || gameboy.cpu.bc != i * 16 - 1
      || gameboy.cpu.getSubtractFlag()
      || gameboy.cpu.getHalfCarryFlag()
    ) {
      std::cout << "No half-carry #" << i << '\n'
                << "Flags: " << (unsigned int) gameboy.cpu.af << '\n'
                << "Value: " << gameboy.cpu.bc << std::endl;

      return false;
    }

    gameboy.cpu.af = 0;

    instruction.execute(gameboy, NULL);

    if (
      gameboy.cpu.getSubtractFlag()
      || !gameboy.cpu.getHalfCarryFlag()
      || gameboy.cpu.getZeroFlag() != (i == 16)
      || gameboy.cpu.bc != (i == 16 ? 0 : i * 16)
    ) {
      std::cout << "Half-carry #" << i << '\n'
                << "Flags: " << (unsigned int) gameboy.cpu.af << '\n'
                << "Value: " << gameboy.cpu.bc << std::endl;

      return false;
    }
  }

  return true;
}
