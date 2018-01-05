#include "instruction.hpp"

bool Instruction::isExtendedInstruction(uint8_t firstOpcodeByte) {
  return firstOpcodeByte == 0xCB;
}

Instruction::Instruction(unsigned long long ticks, unsigned short dataSize, unsigned short opcodeSize):
  ticks(ticks),
  dataSize(dataSize),
  opcodeSize(opcodeSize)
{
}

unsigned short Instruction::totalSize() {
  return dataSize + opcodeSize;
}

