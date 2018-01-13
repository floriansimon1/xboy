#ifndef REGISTER_ROTATE_LEFT_CARRY_HPP
#define REGISTER_ROTATE_LEFT_CARRY_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct RegisterRotateLeftCarry: Instruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  RegisterRotateLeftCarry(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
