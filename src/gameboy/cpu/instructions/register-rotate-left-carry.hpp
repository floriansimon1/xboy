#ifndef REGISTER_ROTATE_LEFT_CARRY_HPP
#define REGISTER_ROTATE_LEFT_CARRY_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct RegisterRotateLeftCarry: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  RegisterRotateLeftCarry(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
