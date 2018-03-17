#ifndef ENABLE_INTERRUPTS_HPP
#define ENABLE_INTERRUPTS_HPP

#include "../constant-time-instruction.hpp"

struct EnableInterrupts: ConstantTimeInstruction {
  const bool enable;

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  EnableInterrupts(bool enable);
};

#endif
