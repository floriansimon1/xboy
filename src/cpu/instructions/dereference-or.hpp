#ifndef DEREFERENCE_OR_HPP
#define DEREFERENCE_OR_HPP

#include "immediate-or.hpp"
#include "../cpu.hpp"

struct DereferenceOr: Instruction {
  CpuRegisterPointer pointerRegister;

  DereferenceOr(CpuRegisterPointer pointerRegister, bool exclusive);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    const ImmediateOr orInstruction;
};

#endif
