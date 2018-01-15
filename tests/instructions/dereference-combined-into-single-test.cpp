#include "../../cpu/instructions/dereference-combined-into-single.hpp"
#include "dereference-combined-into-single-test.hpp"
#include "../../gameboy.hpp"

DereferenceCombinedIntoSingleTest::DereferenceCombinedIntoSingleTest():
  Test("Derefence combined registers into single-byte register instruction")
{
}

bool DereferenceCombinedIntoSingleTest::run() {
  Gameboy                       gameboy;
  DereferenceCombinedIntoSingle instruction(&Cpu::bc, &Cpu::af, true);

  const auto value = 150;

  gameboy.cpu.bc = 10;
  gameboy.cpu.af = 0;

  gameboy.mmu.memory[gameboy.cpu.bc] = value;

  instruction.execute(gameboy, gameboy.mmu.memory);

  return gameboy.cpu.af == value;
}
