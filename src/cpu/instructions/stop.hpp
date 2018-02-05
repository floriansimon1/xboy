#ifndef STOP_HPP
#define STOP_HPP

#include "../constant-time-instruction.hpp"

struct Stop: ConstantTimeInstruction {
  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  Stop();
};

#endif
