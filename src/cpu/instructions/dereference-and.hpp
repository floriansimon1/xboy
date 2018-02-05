#ifndef DEREFERENCE_AND_HPP
#define DEREFERENCE_AND_HPP

#include "immediate-and.hpp"
#include "../cpu.hpp"

struct DereferenceAnd: Instruction {
  CpuRegisterPointer pointerRegister;

  DereferenceAnd(CpuRegisterPointer pointerRegister);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    const ImmediateAnd andInstruction;
};

#endif
