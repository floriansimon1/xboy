#include "decimal-adjust.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"
#include "../cpu.hpp"

DecimalAdjust::DecimalAdjust(): Instruction(4, 0, 1) {
}

void DecimalAdjust::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto result = (
    gameboy.cpu.getSubtractFlag()
    ? subtracting(gameboy)
    : adding(gameboy)
  );

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, result);

  if (!gameboy.cpu.getCarryFlag()) {
    gameboy.cpu.setCarryFlag(result > maxTwoBytesBcd);
  }

  gameboy.cpu.setHalfCarryFlag(false);
  gameboy.cpu.setZeroFlag(!gameboy.cpu.singleByteRegister(&Cpu::af, false));
}

std::string DecimalAdjust::toString() const {
  return "DAA";
}

uint32_t DecimalAdjust::subtracting(Gameboy &gameboy) const {
  uint32_t result = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  if (gameboy.cpu.getHalfCarryFlag()) {
    result = (result - 6) & lowByteMask;
  }

  if (gameboy.cpu.getCarryFlag()) {
    // 6 on the high half-byte.
    result -= 0x60;
  }

  return result;
}

uint32_t DecimalAdjust::adding(Gameboy &gameboy) const {
  uint32_t result = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  if (gameboy.cpu.getHalfCarryFlag() || (result & lowHalfByteMask) > 9) {
    result += 6;
  }

  if (gameboy.cpu.getCarryFlag() || result >= 0x9f) {
    // 6 on the high half-byte.
    result += 0x60;
  }

  return result;
}
