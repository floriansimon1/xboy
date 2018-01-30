#ifndef INVERT_CARRY_FLAG_HPP
#define INVERT_CARRY_FLAG_HPP

#include "../instruction.hpp"

struct InvertCarryFlag: Instruction {
  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  InvertCarryFlag();
};

#endif
