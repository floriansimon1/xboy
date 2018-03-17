#ifndef TWO_BYTES_INCREMENT_HPP
#define TWO_BYTES_INCREMENT_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct TwoBytesIncrement: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;
  const short sign;

  TwoBytesIncrement(CpuRegisterPointer cpuRegister, short sign);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
