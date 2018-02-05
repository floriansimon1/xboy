#ifndef NEGATE_HPP
#define NEGATE_HPP

#include "../instruction.hpp"

struct Negate: Instruction {
  Negate();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
