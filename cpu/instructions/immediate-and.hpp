#ifndef IMMEDIATE_AND_HPP
#define IMMEDIATE_AND_HPP

#include "../instruction.hpp"
#include "../cpu.hpp"

struct ImmediateAnd: Instruction {
  ImmediateAnd();

  void execute(Gameboy &gameboy, const uint8_t *data) const override;
  std::string toString() const override;
};

#endif
