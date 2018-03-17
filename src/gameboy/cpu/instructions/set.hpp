#ifndef SET_HPP
#define SET_HPP

#include <sstream>

#include "../constant-time-instruction.hpp"
#include "../../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "../../../bit.hpp"
#include "../cpu.hpp"

template <unsigned int bit>
struct Set: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  Set(CpuRegisterPointer cpuRegister, bool low):
    ConstantTimeInstruction(8, 0, 2),
    cpuRegister(cpuRegister),
    low(low)
  {
  }

  void execute(Gameboy &gameboy, const uint8_t *) const override {
    const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

    gameboy.cpu.setSingleByteRegister(cpuRegister, low, value | (1 << bit));
  }

  std::string toString() const override {
    std::ostringstream result;

    result << "SET " << bit << ", " << registerString(cpuRegister, true, low);

    return result.str();
  }
};

#endif
