#include "../../src/gameboy.hpp"
#include "load-immediate-16-test.hpp"
#include "../../src/cpu/instructions/load-immediate-16.hpp"

LoadImmediate16Test::LoadImmediate16Test():
  Test("Load immediate 16 instruction")
{
}

bool LoadImmediate16Test::run() {
  Gameboy         gameboy;
  LoadImmediate16 instruction(&Cpu::bc);

  const uint8_t lowByte  = 1;
  const uint8_t highByte = 2;

  uint16_t data = (highByte << 8) | lowByte;

  instruction.execute(gameboy, reinterpret_cast<uint8_t*>(&data));

  return gameboy.cpu.bc == data;
}
