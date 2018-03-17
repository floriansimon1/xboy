#include "instruction.hpp"

bool Instruction::isExtendedInstruction(uint8_t firstOpcodeByte) {
  return firstOpcodeByte == 0xcb;
}

Instruction::Instruction(unsigned short dataSize, unsigned short opcodeSize):
  opcodeSize(opcodeSize),
  dataSize(dataSize)
{
}

unsigned short Instruction::totalSize() {
  return dataSize + opcodeSize;
}
