#ifndef NOP_HPP
#define NOP_HPP

#include "../instruction.hpp"

struct Nop: Instruction {
  void execute(Gameboy &gameboy, const uint8_t *data) override;

  Nop();
};

#endif

