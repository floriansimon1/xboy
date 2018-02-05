#ifndef IMMEDIATE_OR_HPP
#define IMMEDIATE_OR_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct ImmediateOr: Instruction {
  const bool exclusive;

  ImmediateOr(bool exclusive);

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
  const char* mnemonic() const;
};

#endif
