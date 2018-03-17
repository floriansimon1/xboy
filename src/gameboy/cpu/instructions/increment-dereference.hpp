#ifndef INCREMENT_DEREFERENCE_HPP
#define INCREMENT_DEREFERENCE_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct IncrementDereference: ConstantTimeInstruction {
  CpuRegisterPointer pointerRegister;
  const short sign;

  IncrementDereference(CpuRegisterPointer pointerRegister, const short sign);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
