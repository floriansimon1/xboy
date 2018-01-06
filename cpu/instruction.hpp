#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>

struct Gameboy;

struct Instruction {
  const unsigned long long ticks;

  const unsigned short dataSize;
  const unsigned short opcodeSize;

  virtual void execute(Gameboy &gameboy, const uint8_t *data) = 0;

  static bool isExtendedInstruction(uint8_t firstOpcodeByte);

  unsigned short totalSize();

  protected:
    Instruction(unsigned long long ticks, unsigned short dataSize, unsigned short opcodeSize);
};

#endif

