#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

struct Gameboy;

struct Instruction {
  const unsigned int ticks;
  const unsigned int dataSize;
  const unsigned int opcodeSize;

  virtual void execute(Gameboy &gameboy) = 0;

  protected:
    Instruction(unsigned int ticks, unsigned int dataSize, unsigned int opcodeSize);
};

#endif

