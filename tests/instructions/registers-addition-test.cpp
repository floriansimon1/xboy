#include "../../bit.hpp"
#include "../../gameboy.hpp"
#include "./registers-addition-test.hpp"
#include "../../cpu/instructions/add-memory-byte-to-register.hpp"

RegistersAdditionTest::RegistersAdditionTest(): Test("Registers addition test") {
}

bool RegistersAdditionTest::run() {
  AddMemoryByteToRegister withCarry(&Cpu::hl, &Cpu::bc, false, true);
  AddMemoryByteToRegister normal(&Cpu::hl, &Cpu::bc, false, false);
  Gameboy                 gameboy;

  const auto someValue = 8;

  gameboy.cpu.hl = 0;
  gameboy.mmu.memory[gameboy.cpu.hl] = 1;
  gameboy.cpu.setSingleByteRegister(&Cpu::bc, true, someValue);
  gameboy.cpu.setSingleByteRegister(&Cpu::bc, false, maxUint8);

  normal.execute(gameboy, gameboy.mmu.memory);

  if (
    !gameboy.cpu.getZeroFlag()
    || !gameboy.cpu.getCarryFlag()
    || gameboy.cpu.getSubtractFlag()
    || !gameboy.cpu.getHalfCarryFlag()
    || gameboy.cpu.singleByteRegister(&Cpu::bc, false)
    || gameboy.cpu.singleByteRegister(&Cpu::bc, true) != someValue
  ) {
    return false;
  }

  withCarry.execute(gameboy, gameboy.mmu.memory);

  if (
    gameboy.cpu.getZeroFlag()
    || gameboy.cpu.getCarryFlag()
    || gameboy.cpu.getSubtractFlag()
    || gameboy.cpu.getHalfCarryFlag()
    || gameboy.cpu.singleByteRegister(&Cpu::bc, false) != 2
    || gameboy.cpu.singleByteRegister(&Cpu::bc, true) != someValue
  ) {
    return false;
  }

  return true;
}
