#include "constant-time-instruction.hpp"

ConstantTimeInstruction::ConstantTimeInstruction(unsigned long long ticks, unsigned short dataSize, unsigned short opcodeSize):
  Instruction(dataSize, opcodeSize),
  constantTime(ticks)
{
}

unsigned short ConstantTimeInstruction::ticks(Gameboy &) const {
  return constantTime;
}
