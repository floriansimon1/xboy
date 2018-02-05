#ifndef POP_TWO_BYTES_HPP
#define POP_TWO_BYTES_HPP

#include "../cpu.hpp"
#include "../instruction.hpp"

struct PopTwoBytes: Instruction {
  CpuRegisterPointer cpuRegister;

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  PopTwoBytes(CpuRegisterPointer cpuRegister);
};

#endif