#ifndef DEREFERENCE_HPP
#define DEREFERENCE_HPP

#include "../constant-time-instruction.hpp"
#include "../cpu.hpp"

struct Dereference: ConstantTimeInstruction {
  Dereference();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
