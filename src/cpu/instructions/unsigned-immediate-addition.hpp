#ifndef UNSIGNED_IMMEDIATE_ADDITION_HPP
#define UNSIGNED_IMMEDIATE_ADDITION_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct UnsignedImmediateAddition: Instruction {
  const bool carry;

  UnsignedImmediateAddition(bool carry);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
  const char* mnemonic() const;
};

#endif
