#include "../../src/bit.hpp"
#include "../../src/gameboy.hpp"
#include "./registers-addition-test.hpp"
#include "../../src/cpu/instructions/add-memory-byte-to-register.hpp"

RegistersAdditionTest::RegistersAdditionTest(): Test("Registers addition test") {
}

bool RegistersAdditionTest::run() {
  AddMemoryByteToRegister withCarry(&Cpu::hl, true);
  AddMemoryByteToRegister normal(&Cpu::hl, false);
  Gameboy                 gameboy;

  gameboy.cpu.hl = Mmu::ramStart;

  gameboy.mmu.write(gameboy.cpu.hl, 1);

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, maxUint8);

  normal.execute(gameboy, NULL);

  if (
    !gameboy.cpu.getZeroFlag()
    || !gameboy.cpu.getCarryFlag()
    || gameboy.cpu.getSubtractFlag()
    || !gameboy.cpu.getHalfCarryFlag()
    || gameboy.cpu.hl != Mmu::ramStart
    || gameboy.cpu.singleByteRegister(&Cpu::af, false)
  ) {
    return false;
  }

  withCarry.execute(gameboy, NULL);

  if (
    gameboy.cpu.getZeroFlag()
    || gameboy.cpu.getCarryFlag()
    || gameboy.cpu.getSubtractFlag()
    || gameboy.cpu.getHalfCarryFlag()
    || gameboy.cpu.hl != Mmu::ramStart
    || gameboy.cpu.singleByteRegister(&Cpu::af, false) != 2
  ) {
    return false;
  }

  return true;
}
