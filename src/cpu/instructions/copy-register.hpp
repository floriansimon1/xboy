#ifndef COPY_REGISTER_HPP
#define COPY_REGISTER_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct CopyRegister: ConstantTimeInstruction {
  bool               fromLow;
  bool               toLow;
  CpuRegisterPointer from;
  CpuRegisterPointer to;

  CopyRegister(CpuRegisterPointer to, bool toLow, CpuRegisterPointer from, bool fromLow);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
