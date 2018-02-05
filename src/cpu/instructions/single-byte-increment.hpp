#ifndef SINGLE_BYTE_INCREMENT_HPP
#define SINGLE_BYTE_INCREMENT_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct SingleByteIncrement: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const short sign;
  const bool low;

  SingleByteIncrement(CpuRegisterPointer cpuRegister, bool low, short sign);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
