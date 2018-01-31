#ifndef SET_CARRY_FLAG_HPP
#define SET_CARRY_FLAG_HPP

#include "../instruction.hpp"

struct SetCarryFlag: Instruction {
  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  SetCarryFlag();
};

#endif
