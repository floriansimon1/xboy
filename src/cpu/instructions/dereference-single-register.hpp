#ifndef DEREFERENCE_SINGLE_REGISTER_HPP
#define DEREFERENCE_SINGLE_REGISTER_HPP

#include "../constant-time-instruction.hpp"
#include "register-rotate-left.hpp"
#include "../cpu.hpp"

struct DereferenceSingleRegister: ConstantTimeInstruction {
  CpuRegisterPointer source;
  const bool         sourceLow;
  CpuRegisterPointer destination;
  const bool         destinationLow;

  DereferenceSingleRegister(
    CpuRegisterPointer source,
    const bool         sourceLow,
    CpuRegisterPointer destination,
    const bool         destinationLow
  );

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
