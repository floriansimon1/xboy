#ifndef DECIMAL_ADJUST_HPP
#define DECIMAL_ADJUST_HPP

#include "../instruction.hpp"

struct DecimalAdjust: Instruction {
  DecimalAdjust();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  private:
    uint16_t adding(Gameboy &gameboy) const;
    uint16_t subtracting(Gameboy &gameboy) const;
};

#endif
