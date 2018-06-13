#ifndef UNSIGNED_IMMEDIATE_ADDITION_HPP
#define UNSIGNED_IMMEDIATE_ADDITION_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct UnsignedImmediateAddition: ConstantTimeInstruction {
  const bool carry;

  UnsignedImmediateAddition(bool carry);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
  std::string mnemonic() const;
};

#endif
