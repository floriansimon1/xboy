#ifndef NOP_HPP
#define NOP_HPP

#include "../constant-time-instruction.hpp"

struct Nop: ConstantTimeInstruction {
  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  Nop();
};

#endif
