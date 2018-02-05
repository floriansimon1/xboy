#ifndef IMMEDIATE_OR_HPP
#define IMMEDIATE_OR_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct ImmediateOr: ConstantTimeInstruction {
  const bool exclusive;

  ImmediateOr(bool exclusive);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
  const char* mnemonic() const;
};

#endif
