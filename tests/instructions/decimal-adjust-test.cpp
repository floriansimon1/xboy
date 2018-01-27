#include <iostream>

#include "../../gameboy.hpp"
#include "decimal-adjust-test.hpp"
#include "../../cpu/instructions/decimal-adjust.hpp"

DecimalAdjustTest::DecimalAdjustTest():
  Test("Decimal adjust instruction")
{
}

bool DecimalAdjustTest::run() {
  Gameboy       gameboy;
  DecimalAdjust instruction;

  // 9        + 5
  // 0b1001   + 0b101
  // ------------------
  // 14
  // 0b1110
  // BCD: 0b00010100
  // BCD: 20
  // C = 0, H = 0, Z = 0, N = 0
  gameboy.cpu.setSingleByteRegister(&Cpu::af, true, 0);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 14);

  instruction.execute(gameboy, gameboy.mmu.memory);

  if (
    gameboy.cpu.singleByteRegister(&Cpu::af, true)
    || gameboy.cpu.singleByteRegister(&Cpu::af, false) != 20
  ) {
    std::cout << "9 + 5 != 20: f = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true)
              << ", a = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, false)
              << std::endl;

    return false;
  }

  return true;
}
