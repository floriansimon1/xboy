#include "instruction.hpp"

bool Instruction::isExtendedInstruction(uint8_t firstOpcodeByte) {
  return firstOpcodeByte == 0xCB;
}

Instruction::Instruction(unsigned int ticks, unsigned int dataSize, unsigned int opcodeSize):
  ticks(ticks),
  dataSize(dataSize),
  opcodeSize(opcodeSize)
{
}
