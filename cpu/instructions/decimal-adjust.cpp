#include "decimal-adjust.hpp"
#include "../../cpu.hpp"
#include "../../bit.hpp"

void DecimalAdjust::execute(Gameboy &gameboy, const uint8_t *) const {
  const auto result = (
    gameboy.cpu.getSubtractFlag()
    ? subtracting(gameboy)
    : adding(gameboy)
  );

  gameboy.cpu.setSingleByteRegister(&Cpu::af, false, result);

  gameboy.cpu.setHalfCarryFlag(false);
  gameboy.cpu.setCarryFlag(result > maxUint16);
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
    result -= 0x60;
  }

  return result;
}

uint32_t DecimalAdjust::adding(Gameboy &gameboy) const {
  uint32_t result = gameboy.cpu.singleByteRegister(&Cpu::af, false);

  if (gameboy.cpu.getHalfCarryFlag() || (result & lowHalfByteMask) > 9) {
    result += 6;
  }

  if (gameboy.cpu.getCarryFlag() || result > 0x9f) {
    result += 0x60;
  }

  return result;
}
