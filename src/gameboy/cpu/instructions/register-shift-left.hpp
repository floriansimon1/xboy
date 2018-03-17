#ifndef REGISTER_SHIFT_LEFT_HPP
#define REGISTER_SHIFT_LEFT_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct RegisterShiftLeft: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  RegisterShiftLeft(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
