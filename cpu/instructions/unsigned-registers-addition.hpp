#ifndef UNSIGNED_REGISTER_ADDITION_HPP
#define UNSIGNED_REGISTER_ADDITION_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct UnsignedRegisterAddition: Instruction {
  bool               fromLow;
  bool               toLow;
  CpuRegisterPointer from;
  CpuRegisterPointer to;

  UnsignedRegisterAddition(CpuRegisterPointer to, bool toLow, CpuRegisterPointer from, bool fromLow);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
