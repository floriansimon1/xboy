#include "instruction.hpp"

bool Instruction::isExtendedInstruction(uint8_t firstOpcodeByte) {
  return firstOpcodeByte == 0xCB;
}

Instruction::Instruction(unsigned long long ticks, unsigned short dataSize, unsigned short opcodeSize):
  opcodeSize(opcodeSize),
  dataSize(dataSize),
  baseTicks(ticks)
{
}

unsigned short Instruction::totalSize() {
  return dataSize + opcodeSize;
}

unsigned short Instruction::ticks(Gameboy &) const {
  return baseTicks;
}
