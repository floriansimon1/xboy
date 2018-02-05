#ifndef PUSH_TWO_BYTES_HPP
#define PUSH_TWO_BYTES_HPP

#include "../cpu.hpp"
#include "../constant-time-instruction.hpp"

struct PushTwoBytes: ConstantTimeInstruction {
  CpuRegisterPointer cpuRegister;

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  PushTwoBytes(CpuRegisterPointer cpuRegister);
};

#endif
