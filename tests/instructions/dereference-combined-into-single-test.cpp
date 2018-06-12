#include "../../src/gameboy/cpu/instructions/dereference-combined-into-single-increment.hpp"
#include "../../src/gameboy/cpu/instructions/dereference-combined-into-single.hpp"
#include "dereference-combined-into-single-test.hpp"
#include "../../src/gameboy/gameboy.hpp"

DereferenceCombinedIntoSingleTest::DereferenceCombinedIntoSingleTest():
  Test("Dereference a word register into a byte register instruction")
{
}

bool DereferenceCombinedIntoSingleTest::run() {
  Gameboy                                gameboy;
  DereferenceCombinedIntoSingle          instruction(&Cpu::bc, &Cpu::af, true);
  DereferenceCombinedIntoSingleIncrement withIncrement(&Cpu::bc, &Cpu::af, 1, true);

  const auto value = 150;

  gameboy.cpu.bc = Mmu::ramStart;
  gameboy.cpu.af = 0;

  gameboy.mmu.write(gameboy, gameboy.cpu.bc, value);

  instruction.execute(gameboy, NULL);

  if (gameboy.cpu.af != value || gameboy.cpu.bc != Mmu::ramStart) {
    return false;
  }

  gameboy.cpu.af = 0;

  withIncrement.execute(gameboy, NULL);

  return gameboy.cpu.af == value && gameboy.cpu.bc == Mmu::ramStart + 1;
}
