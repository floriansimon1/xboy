#ifndef UNSIGNED_IMMEDIATE_SUBTRACTION_HPP
#define UNSIGNED_IMMEDIATE_SUBTRACTION_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct UnsignedImmediateSubtraction: Instruction {
  const bool carry;

  UnsignedImmediateSubtraction(bool carry);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
  const char* mnemonic() const;
};

#endif
