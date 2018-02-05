#include "../../src/bit.hpp"
#include "../../src/gameboy.hpp"
#include "two-bytes-decrement-test.hpp"
#include "../../src/cpu/instructions/two-bytes-increment.hpp"

TwoBytesDecrementTest::TwoBytesDecrementTest():
  Test("Two-bytes decrement instruction")
{
}

bool TwoBytesDecrementTest::run() {
  Gameboy           gameboy;
  TwoBytesIncrement instruction(&Cpu::bc, -1);

  gameboy.cpu.bc = 0;

  instruction.execute(gameboy, gameboy.mmu.memory);

  if (gameboy.cpu.bc != maxUint16) {
    return false;
  }

  gameboy.cpu.bc = 1;

  instruction.execute(gameboy, gameboy.mmu.memory);

  return !gameboy.cpu.bc;
}
