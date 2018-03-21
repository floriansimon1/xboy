#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>
#include <string>

struct Gameboy;

struct Instruction {
  virtual ~Instruction() = default;

  const unsigned short opcodeSize;
  const unsigned short dataSize;

  virtual void execute(Gameboy &gameboy, const uint8_t *data) const = 0;
  virtual std::string toString() const = 0;

  static bool isExtendedInstruction(uint8_t firstOpcodeByte);

  unsigned short totalSize();
  virtual unsigned short ticks(Gameboy &gameboy) const = 0;

  protected:
    Instruction(unsigned short dataSize, unsigned short opcodeSize);
};

#endif
