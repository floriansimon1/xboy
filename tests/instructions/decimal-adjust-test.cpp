#include <iostream>

#include "../../bit.hpp"
#include "../../gameboy.hpp"
#include "decimal-adjust-test.hpp"
#include "../../cpu/instructions/decimal-adjust.hpp"

DecimalAdjustTest::DecimalAdjustTest():
  Test("Decimal adjust instruction")
{
}

bool DecimalAdjustTest::run() {
  if (!testLowByteAddition()) return false;
  if (!testHighByteAddition()) return false;
  if (!testLowByteSubtraction()) return false;
  if (!testHighByteSubtraction()) return false;
  if (!testCombinedCarriesAddition()) return false;
  if (!testCombinedCarriesSubtraction()) return false;

  return true;
}

bool DecimalAdjustTest::testCombinedCarriesAddition() const {
  Gameboy       gameboy;
  DecimalAdjust instruction;

  const uint8_t carryBit = setBit(0, Cpu::carryFlag, true);
  const uint8_t zeroBit  = setBit(0, Cpu::zeroFlag, true);

  // 99         + 1
  // BCD
  // 0b10011001 + 1
  // -----------------------
  // 0b10011010 (0x9A)
  // Expected BCD: 100 (0b100000000)
  // Truncated: 0
  // C = 0, H = 0, Z = 0, N = 0
  gameboy.cpu.setSingleByteRegister(&Cpu::af, true, 0);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 0x9A);

  instruction.execute(gameboy, gameboy.mmu.memory);

  if (
    gameboy.cpu.singleByteRegister(&Cpu::af, true) != (carryBit | zeroBit)
    || gameboy.cpu.singleByteRegister(&Cpu::af, false)
  ) {
    std::cout << "99 + 1 != 0: f = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true)
              << ", a = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, false)
              << std::endl;

    return false;
  }

  return true;
}

bool DecimalAdjustTest::testLowByteAddition() const {
  Gameboy       gameboy;
  DecimalAdjust instruction;

  const uint8_t halfCarryBit = setBit(0, Cpu::halfCarryFlag, true);

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

  // 9        + 8
  // 0b1001   + 0b1000
  // ------------------
  // 17
  // 0b10001
  // BCD: 0b00010111
  // BCD: 23
  // C = 0, H = 1, Z = 0, N = 0
  gameboy.cpu.setSingleByteRegister(&Cpu::af, true, halfCarryBit);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 17);

  instruction.execute(gameboy, gameboy.mmu.memory);

  if (
    gameboy.cpu.singleByteRegister(&Cpu::af, true)
    || gameboy.cpu.singleByteRegister(&Cpu::af, false) != 23
  ) {
    std::cout << "9 + 8 != 23: f = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true)
              << ", a = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, false)
              << std::endl;

    return false;
  }

  return true;
}

bool DecimalAdjustTest::testHighByteAddition() const {
  Gameboy       gameboy;
  DecimalAdjust instruction;

  const uint8_t carryBit = setBit(0, Cpu::carryFlag, true);

  // 90        + 50
  // BCD
  // 0b10010000 + 0b01010000
  // -----------------------
  // 0b11100000 (decimal 224)
  // Expected BCD: 140 (0b101000000)
  // Truncated: 64 (0b1000000)
  // C = 0, H = 0, Z = 0, N = 0
  gameboy.cpu.setSingleByteRegister(&Cpu::af, true, 0);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 224);

  instruction.execute(gameboy, gameboy.mmu.memory);

  if (
    gameboy.cpu.singleByteRegister(&Cpu::af, true) != carryBit
    || gameboy.cpu.singleByteRegister(&Cpu::af, false) != 64
  ) {
    std::cout << "90 + 50 != 64: f = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true)
              << ", a = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, false)
              << std::endl;

    return false;
  }

  // 90        + 80
  // BCD
  // 0b10010000 + 0b010000000
  // -----------------------
  // 0b100010000
  // Truncated: 0b00010000 (16)
  // Expected BCD: 170 (0b101110000)
  // Truncated: 112 (0b1110000)
  // C = 1, H = 0, Z = 0, N = 0
  gameboy.cpu.setSingleByteRegister(&Cpu::af, true, carryBit);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 16);

  instruction.execute(gameboy, gameboy.mmu.memory);

  if (
    gameboy.cpu.singleByteRegister(&Cpu::af, true) != carryBit
    || gameboy.cpu.singleByteRegister(&Cpu::af, false) != 112
  ) {
    std::cout << "90 + 80 != 112: f = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true)
              << ", a = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, false)
              << std::endl;

    return false;
  }

  return true;
}

bool DecimalAdjustTest::testLowByteSubtraction() const {
    Gameboy       gameboy;
    DecimalAdjust instruction;

    const uint8_t halfCarryBit = setBit(0, Cpu::halfCarryFlag, true);
    const uint8_t subtractBit  = setBit(0, Cpu::subtractFlag, true);
    const uint8_t carryBit     = setBit(0, Cpu::carryFlag, true);

    // 5     - 9
    // 0b101 - 0b1001
    // ------------------
    // 0b11111100 (252)
    // Expected signed BCD: -4
    // Unsigned BCD w/ 10-complement: 96 (0b10010110)
    // C = 1, H = 1, Z = 0, N = 1
    gameboy.cpu.setSingleByteRegister(&Cpu::af, true, subtractBit | halfCarryBit | carryBit);
    gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 252);

    instruction.execute(gameboy, gameboy.mmu.memory);

    if (
      gameboy.cpu.singleByteRegister(&Cpu::af, true) != (subtractBit | carryBit)
      || gameboy.cpu.singleByteRegister(&Cpu::af, false) != 0x96
    ) {
      std::cout << "9 - 5 != 0x96: f = "
                << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true)
                << ", a = "
                << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, false)
                << std::endl;

      return false;
    }

    return true;
}

bool DecimalAdjustTest::testHighByteSubtraction() const {
  Gameboy       gameboy;
  DecimalAdjust instruction;

  const uint8_t subtractBit  = setBit(0, Cpu::subtractFlag, true);
  const uint8_t carryBit     = setBit(0, Cpu::carryFlag, true);

  // 50         - 90
  // 0b01010000 - 0b10010000
  // 0b01010000 + 0b01110000
  // -----------------------
  // 0b11000000 (192)
  // Expected signed BCD: -40
  // Unsigned BCD w/ 10-complement: 60
  // C = 1, H = 0, Z = 0, N = 1
  gameboy.cpu.setSingleByteRegister(&Cpu::af, true, subtractBit | carryBit);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 192);

  instruction.execute(gameboy, gameboy.mmu.memory);

  if (
    gameboy.cpu.singleByteRegister(&Cpu::af, true) != (subtractBit | carryBit)
    || gameboy.cpu.singleByteRegister(&Cpu::af, false) != 0x60
  ) {
    std::cout << "90 - 50 != 0x60: f = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true)
              << ", a = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, false)
              << std::endl;

    return false;
  }

  return true;
}

bool DecimalAdjustTest::testCombinedCarriesSubtraction() const {
  Gameboy       gameboy;
  DecimalAdjust instruction;

  const uint8_t halfCarryBit = setBit(0, Cpu::halfCarryFlag, true);
  const uint8_t subtractBit  = setBit(0, Cpu::subtractFlag, true);
  const uint8_t carryBit     = setBit(0, Cpu::carryFlag, true);

  // 98         - 99
  // 0b10011000 - 0b10011001
  // 0b10011000 + 0b01100111
  // -----------------------
  // 0b11111111 (255)
  // Expected signed BCD: -1
  // Unsigned BCD w/ 10-complement: 99
  // C = 1, H = 1, Z = 0, N = 1
  gameboy.cpu.setSingleByteRegister(&Cpu::af, true, subtractBit | halfCarryBit | carryBit);
  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, 255);

  instruction.execute(gameboy, gameboy.mmu.memory);

  if (
    gameboy.cpu.singleByteRegister(&Cpu::af, true) != (subtractBit | carryBit)
    || gameboy.cpu.singleByteRegister(&Cpu::af, false) != 0x99
  ) {
    std::cout << "98 - 99 != 0x99: f = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, true)
              << ", a = "
              << (unsigned int) gameboy.cpu.singleByteRegister(&Cpu::af, false)
              << std::endl;

    return false;
  }

  return true;
}
