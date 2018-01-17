#include "instruction.hpp"

bool Instruction::isExtendedInstruction(uint8_t firstOpcodeByte) {
  return firstOpcodeByte == 0xCB;
}

Instruction::Instruction(unsigned long long ticks, unsigned short dataSize, unsigned short opcodeSize):
  baseTicks(ticks),
  dataSize(dataSize),
  opcodeSize(opcodeSize)
{
}

unsigned short Instruction::totalSize() {
  return dataSize + opcodeSize;
}

unsigned short Instruction::ticks(Gameboy &, const uint8_t *) const {
  return baseTicks;
}
