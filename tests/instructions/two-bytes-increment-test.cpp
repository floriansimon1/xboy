#include "../../src/bit.hpp"
#include "../../src/gameboy/gameboy.hpp"
#include "two-bytes-increment-test.hpp"
#include "../../src/gameboy/cpu/instructions/two-bytes-increment.hpp"

TwoBytesIncrementTest::TwoBytesIncrementTest():
  Test("Two-bytes increment instruction")
{
}

bool TwoBytesIncrementTest::run() {
  Gameboy           gameboy;
  TwoBytesIncrement instruction(&Cpu::bc, 1);

  gameboy.cpu.bc = maxUint16;

  instruction.execute(gameboy, NULL);

  if (gameboy.cpu.bc) {
    return false;
  }

  gameboy.cpu.bc = 0;

  instruction.execute(gameboy, NULL);

  return gameboy.cpu.bc == 1;
}
