#ifndef NOP_HPP
#define NOP_HPP

#include <string>

#include "../instruction.hpp"

struct Nop: Instruction {
  void execute(Gameboy &gameboy, const uint8_t *data) override;
  std::string toString() override;

  Nop();
};

#endif

