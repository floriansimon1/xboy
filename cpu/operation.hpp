#ifndef OPERATION_HPP
#define OPERATION_HPP

struct Gameboy;

struct Operation {
  const unsigned int ticks;
  const unsigned int instructionSize;

  virtual void execute(Gameboy &gameboy) = 0;

  protected:
    Operation(unsigned int ticks, unsigned int instructionSize);
};

#endif

