#ifndef HALT_HPP
#define HALT_HPP

#include "../instruction.hpp"

struct Halt: Instruction {
  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;

  Halt();
};

#endif
