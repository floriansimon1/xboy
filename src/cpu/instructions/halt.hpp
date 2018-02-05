#ifndef HALT_HPP
#define HALT_HPP

#include "../constant-time-instruction.hpp"

struct Halt: ConstantTimeInstruction {
  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  Halt();
};

#endif
