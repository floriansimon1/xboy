#include <iostream>

#include "../../src/bit.hpp"
#include "../../src/gameboy/gameboy.hpp"
#include "./registers-subtraction-test.hpp"
#include "../../src/gameboy/cpu/instructions/subtract-memory-byte-to-register.hpp"

RegistersSubtractionTest::RegistersSubtractionTest(): Test("Registers subtraction test") {
}

bool RegistersSubtractionTest::run() {
  SubtractMemoryByteToRegister withCarry(&Cpu::hl, true);
  SubtractMemoryByteToRegister normal(&Cpu::hl, false);
  Gameboy                      gameboy;

  gameboy.cpu.hl = Mmu::ramStart;

  gameboy.mmu.write(gameboy, gameboy.cpu.hl, 1);

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 0);

  normal.execute(gameboy, NULL);

  if (
    gameboy.cpu.getZeroFlag()
    || !gameboy.cpu.getCarryFlag()
    || !gameboy.cpu.getSubtractFlag()
    || !gameboy.cpu.getHalfCarryFlag()
    || gameboy.cpu.singleByteRegister(&Cpu::af, false) != maxUint8
  ) {
    std::cout << "0 - 1: " << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, false)
              << ", flags: " << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true)
              << std::endl;

    return false;
  }

  withCarry.execute(gameboy, NULL);

  if (
    gameboy.cpu.getZeroFlag()
    || gameboy.cpu.getCarryFlag()
    || !gameboy.cpu.getSubtractFlag()
    || gameboy.cpu.getHalfCarryFlag()
    || gameboy.cpu.singleByteRegister(&Cpu::af, false) != maxUint8 - 2
  ) {
    std::cout << "maxUint8 - 1 w/ carry: " << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, false)
              << ", flags: " << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true)
              << std::endl;

    return false;
  }

  return true;
}
