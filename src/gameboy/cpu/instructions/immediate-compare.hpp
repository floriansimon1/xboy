#ifndef IMMEDIATE_COMPARE_HPP
#define IMMEDIATE_COMPARE_HPP

#include "./unsigned-immediate-subtraction.hpp"
#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct ImmediateCompare: ConstantTimeInstruction {
  ImmediateCompare();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    const UnsignedImmediateSubtraction subtractionInstruction;
};

#endif
