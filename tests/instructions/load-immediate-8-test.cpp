#include "../../src/gameboy.hpp"
#include "load-immediate-8-test.hpp"
#include "../../src/cpu/instructions/load-immediate-8.hpp"

LoadImmediate8Test::LoadImmediate8Test():
  Test("Load immediate 8 instruction")
{
}

bool LoadImmediate8Test::run() {
  Gameboy        gameboy;
  LoadImmediate8 instruction(&Cpu::bc, false);

  const uint8_t value = 111;

  instruction.execute(gameboy, &value);

  return gameboy.cpu.singleByteRegister(instruction.cpuRegister, instruction.low) == value;
}
