#ifndef UNMAPPED_HPP
#define UNMAPPED_HPP

#include "../constant-time-instruction.hpp"

struct Unmapped: ConstantTimeInstruction {
  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  Unmapped();
};

#endif
