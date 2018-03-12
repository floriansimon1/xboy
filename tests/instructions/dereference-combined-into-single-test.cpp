#include "../../src/cpu/instructions/dereference-combined-into-single.hpp"
#include "dereference-combined-into-single-test.hpp"
#include "../../src/gameboy.hpp"

DereferenceCombinedIntoSingleTest::DereferenceCombinedIntoSingleTest():
  Test("Dereference a word register into a byte register instruction")
{
}

bool DereferenceCombinedIntoSingleTest::run() {
  Gameboy                       gameboy;
  DereferenceCombinedIntoSingle instruction(&Cpu::bc, &Cpu::af, true);

  const auto value = 150;

  gameboy.cpu.bc = 10;
  gameboy.cpu.af = 0;

  gameboy.mmu.write(gameboy.cpu.bc, value);

  instruction.execute(gameboy, NULL);

  return gameboy.cpu.af == value;
}
