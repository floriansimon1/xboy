#ifndef LOAD_IMMEDIATE_8_HPP
#define LOAD_IMMEDIATE_8_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct LoadImmediate8: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  LoadImmediate8(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
