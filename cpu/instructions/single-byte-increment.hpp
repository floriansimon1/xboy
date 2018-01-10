#ifndef SINGLE_BYTE_INCREMENT_HPP
#define SINGLE_BYTE_INCREMENT_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct SingleByteIncrement: Instruction {
  CpuRegisterPointer cpuRegister;
  const short sign;
  const bool low;

  SingleByteIncrement(CpuRegisterPointer cpuRegister, bool low, short sign);

  void execute(Gameboy &gameboy, const uint8_t *data) override;
  std::string toString() override;
};

#endif
