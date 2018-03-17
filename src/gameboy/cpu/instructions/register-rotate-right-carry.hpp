#ifndef REGISTER_ROTATE_RIGHT_CARRY_HPP
#define REGISTER_ROTATE_RIGHT_CARRY_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct RegisterRotateRightCarry: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  RegisterRotateRightCarry(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
