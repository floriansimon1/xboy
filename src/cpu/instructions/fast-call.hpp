#ifndef CALL_HPP
#define CALL_HPP

#include "../constant-time-instruction.hpp"
#include "../../gameboy.hpp"

struct FastCall: ConstantTimeInstruction {
  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  FastCall();
};

#endif
