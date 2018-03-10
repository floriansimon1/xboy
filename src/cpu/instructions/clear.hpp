#ifndef CLEAR_HPP
#define CLEAR_HPP

#include <sstream>

#include "../constant-time-instruction.hpp"
#include "../../debug/register-string.hpp"
#include "../../gameboy.hpp"
#include "../../bit.hpp"
#include "../cpu.hpp"

template <unsigned int bit>
struct Clear: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  Clear(CpuRegisterPointer cpuRegister, bool low):
    ConstantTimeInstruction(8, 0, 2),
    cpuRegister(cpuRegister),
    low(low)
  {
  }

  void execute(Gameboy &gameboy, const uint8_t *) const override {
    const auto value = gameboy.cpu.singleByteRegister(cpuRegister, low);

    const uint8_t mask = static_cast<uint8_t>(~(1 << bit));

    gameboy.cpu.setSingleByteRegister(cpuRegister, low, value & mask);
  }

  std::string toString() const override {
    std::ostringstream result;

    result << "RES " << bit << ", " << registerString(cpuRegister, true, low);

    return result.str();
  }
};

#endif
