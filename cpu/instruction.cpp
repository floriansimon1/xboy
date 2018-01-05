#include "instruction.hpp"

Instruction::Instruction(unsigned int ticks, unsigned int dataSize, unsigned int opcodeSize):
  ticks(ticks),
  dataSize(dataSize),
  opcodeSize(opcodeSize)
{
}
