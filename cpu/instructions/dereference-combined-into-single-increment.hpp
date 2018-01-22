#ifndef DEREFERENCE_COMBINED_INTO_SINGLE_INCREMENT_HPP
#define DEREFERENCE_COMBINED_INTO_SINGLE_INCREMENT_HPP

#include "dereference-combined-into-single.hpp"

struct DereferenceCombinedIntoSingleIncrement: Instruction {
  const DereferenceCombinedIntoSingle dereferenceInstruction;
  const short                         sign;

  DereferenceCombinedIntoSingleIncrement(
    CpuRegisterPointer pointerRegister,
    CpuRegisterPointer targetRegister,
    short              sign,
    bool               low
  );

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
