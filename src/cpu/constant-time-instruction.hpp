#ifndef CONSTANT_TIME_INSTRUCTION_HPP
#define CONSTANT_TIME_INSTRUCTION_HPP

#include "instruction.hpp"

struct ConstantTimeInstruction: Instruction {
  ConstantTimeInstruction(unsigned long long ticks, unsigned short dataSize, unsigned short opcodeSize);

  unsigned short ticks(Gameboy &) const override;

  private:
    const unsigned long long constantTime;
};

#endif
