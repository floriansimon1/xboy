#ifndef DEREFERENCE_COMPARE_HPP
#define DEREFERENCE_COMPARE_HPP

#include "immediate-compare.hpp"
#include "../cpu.hpp"

struct DereferenceCompare: Instruction {
  CpuRegisterPointer pointerRegister;

  DereferenceCompare(CpuRegisterPointer pointerRegister);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    const ImmediateCompare compareInstruction;
};

#endif
