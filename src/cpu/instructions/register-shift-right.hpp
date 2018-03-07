#ifndef REGISTER_SHIFT_RIGHT_HPP
#define REGISTER_SHIFT_RIGHT_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct RegisterShiftRight: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  RegisterShiftRight(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
