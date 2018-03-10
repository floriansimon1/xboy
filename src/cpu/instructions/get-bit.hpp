#ifndef GET_BIT_HPP
#define GET_BIT_HPP

#include <sstream>

#include "../constant-time-instruction.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"
#include "../cpu.hpp"

template <unsigned int bit>
struct GetBit: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  GetBit(CpuRegisterPointer cpuRegister, bool low):
    ConstantTimeInstruction(8, 0, 2),
    cpuRegister(cpuRegister),
    low(low)
  {
  }

  void execute(Gameboy &gameboy, const uint8_t *) const override {
    const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

    const auto result = value & getBit(value, bit);

    gameboy.cpu.setHalfCarryFlag(true);
    gameboy.cpu.setSubtractFlag(false);
    gameboy.cpu.setZeroFlag(!result);
  }

  std::string toString() const override {
    std::ostringstream result;

    result << "BIT " << bit << ", " << registerString(cpuRegister, true, low);

    return result.str();
  }
};

#endif
