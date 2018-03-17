#ifndef NEGATE_HPP
#define NEGATE_HPP

#include "../constant-time-instruction.hpp"

struct Negate: ConstantTimeInstruction {
  Negate();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
