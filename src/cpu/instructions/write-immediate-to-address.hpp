#ifndef WRITE_IMMEDIATE_TO_ADDRESS_HPP
#define WRITE_IMMEDIATE_TO_ADDRESS_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct WriteImmediateToAddress: ConstantTimeInstruction {
  CpuRegisterPointer pointerRegister;

  WriteImmediateToAddress(CpuRegisterPointer pointerRegister);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
