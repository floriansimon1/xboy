#ifndef REGISTER_SHIFT_RIGHT_HPP
#define REGISTER_SHIFT_RIGHT_HPP

#include <sstream>

#include "../constant-time-instruction.hpp"
#include "../../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "../../../bit.hpp"
#include "../cpu.hpp"

template <bool arithmetic>
struct RegisterShiftRight: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  RegisterShiftRight(CpuRegisterPointer cpuRegister, bool low):
    ConstantTimeInstruction(8, 0, 2),
    cpuRegister(cpuRegister),
    low(low)
  {
  }

  void execute(Gameboy &gameboy, const uint8_t *) const override {
    const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

    // http://z80-heaven.wikidot.com/instructions-set:sra
    const auto highByte = arithmetic ? value & highBitInByte : 0;

    const auto result = highByte | (value >> 1);

    gameboy.cpu.setCarryFlag(getBit(value, 0));
    gameboy.cpu.setHalfCarryFlag(false);
    gameboy.cpu.setSubtractFlag(false);
    gameboy.cpu.setZeroFlag(!result);

    gameboy.cpu.setSingleByteRegister(cpuRegister, low, result);
  }

  std::string toString() const override {
    std::ostringstream result;

    result << (arithmetic ? "SRA " : "SRL ") << registerString(cpuRegister, true, low);

    return result.str();
  }
};

#endif
