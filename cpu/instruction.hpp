#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>
#include <string>

struct Gameboy;

struct Instruction {
  const unsigned short dataSize;
  const unsigned short opcodeSize;

  virtual void execute(Gameboy &gameboy, const uint8_t *data) const = 0;
  virtual std::string toString() const = 0;

  static bool isExtendedInstruction(uint8_t firstOpcodeByte);

  unsigned short totalSize();
  virtual unsigned short ticks(Gameboy &gameboy, const uint8_t *data) const;

  protected:
    Instruction(unsigned long long ticks, unsigned short dataSize, unsigned short opcodeSize);

  private:
    const unsigned long long baseTicks;
};

#endif
