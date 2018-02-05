#ifndef REGISTER_ROTATE_LEFT_HPP
#define REGISTER_ROTATE_LEFT_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct RegisterRotateLeft: Instruction {
  CpuRegisterPointer cpuRegister;
  const bool         low;

  RegisterRotateLeft(CpuRegisterPointer cpuRegister, bool low);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
