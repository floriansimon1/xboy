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

  const uint16_t lowByte  = 0b10111101;
  const uint16_t highByte = 0b11011011;

  gameboy.mmu.memory[0] = 1;
  gameboy.cpu.bc        = (highByte << 8) | lowByte;

  instruction.execute(gameboy, gameboy.mmu.memory);

  return gameboy.cpu.bc == ((1 << 8) | lowByte);
}
