#include "../../src/bit.hpp"
#include "../../src/gameboy/gameboy.hpp"
#include "two-bytes-decrement-test.hpp"
#include "../../src/gameboy/cpu/instructions/two-bytes-increment.hpp"

TwoBytesDecrementTest::TwoBytesDecrementTest():
  Test("Two-bytes decrement instruction")
{
}

bool TwoBytesDecrementTest::run() {
  Gameboy           gameboy;
  TwoBytesIncrement instruction(&Cpu::bc, -1);

  gameboy.cpu.bc = 0;

  instruction.execute(gameboy, NULL);

  if (gameboy.cpu.bc != maxUint16) {
    return false;
  }

  gameboy.cpu.bc = 1;

  instruction.execute(gameboy, NULL);

  return !gameboy.cpu.bc;
}
