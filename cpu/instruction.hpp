#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>

struct Gameboy;

struct Instruction {
  const unsigned long long ticks;

  const unsigned short dataSize;
  const unsigned short opcodeSize;

  static bool isExtendedInstruction(uint8_t firstOpcodeByte);

  virtual void execute(Gameboy &gameboy) = 0;
  unsigned short totalSize();

  protected:
    Instruction(unsigned long long ticks, unsigned short dataSize, unsigned short opcodeSize);
};

#endif

