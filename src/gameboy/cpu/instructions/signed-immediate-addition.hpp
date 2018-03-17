#ifndef SIGNED_IMMEDIATE_ADDITION_HPP
#define SIGNED_IMMEDIATE_ADDITION_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct SignedImmediateAddition: ConstantTimeInstruction {
  SignedImmediateAddition();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
