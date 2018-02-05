#ifndef LOAD_IMMEDIATE_16_HPP
#define LOAD_IMMEDIATE_16_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct LoadImmediate16: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;

  LoadImmediate16(CpuRegisterPointer cpuRegister);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
