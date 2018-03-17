#ifndef DECIMAL_ADJUST_HPP
#define DECIMAL_ADJUST_HPP

#include "../constant-time-instruction.hpp"

struct DecimalAdjust: ConstantTimeInstruction {
  DecimalAdjust();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    uint32_t adding(Gameboy &gameboy) const;
    uint32_t subtracting(Gameboy &gameboy) const;
};

#endif
