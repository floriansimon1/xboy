#ifndef DEREFERENCE_COMBINED_INTO_SINGLE_HPP
#define DEREFERENCE_COMBINED_INTO_SINGLE_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct DereferenceCombinedIntoSingle: ConstantTimeInstruction {
  CpuRegisterPointer pointerRegister;
  CpuRegisterPointer targetRegister;
  const bool         low;

  DereferenceCombinedIntoSingle(
    CpuRegisterPointer pointerRegister,
    CpuRegisterPointer targetRegister,
    bool               low
  );

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
